/*
 * main.cpp – ESP32 entry-point for the VisionHelicopter Simulink ERT model.
 *
 * Model details (from generated code):
 *   - ERT target, ODE3 fixed-step solver
 *   - Base sample time: 1.3 seconds per model step
 *   - 20 continuous states
 *   - Setpoints baked in: altitude reference = 5 m, vx = 1 m/s (x), vy = 1 m/s (y)
 *   - Outputs: Pitch (rad), Roll (rad), Altitude (m), vx (m/s), vy (m/s)
 *   - NOTE: Yaw is NOT modeled in this helicopter (no anti-torque/yaw channel).
 *           We compute and display velocity heading as a proxy for yaw.
 *
 * Serial output: 115200 baud
 * Flash:  pio run --target upload
 * Monitor: pio device monitor
 */

#include <Arduino.h>
#include <cmath>
#include "VisionHelicopter.h"

// -----------------------------------------------------------------------
// Model instance pointer (Dynamically allocated in setup to avoid static init issues)
// -----------------------------------------------------------------------
static VisionHelicopter* model = nullptr;

// -----------------------------------------------------------------------
// ODE derivative scratch buffer – must exist for the lifetime of the model.
// nXc = 20 continuous states (hardcoded in ODE3 integrator).
// -----------------------------------------------------------------------
static double gDerBuf[20] = { 0.0 };

// -----------------------------------------------------------------------
// Convenience pointer to the Real-Time Model struct
// -----------------------------------------------------------------------
static VisionHelicopter::RT_MODEL_VisionHelicopter_T *rtm = nullptr;

// -----------------------------------------------------------------------
// Wall-clock step timing
// We call model->step() every STEP_INTERVAL_MS.
// Each call advances the simulated time by 1.3 s (model base step size).
// -----------------------------------------------------------------------
static const uint32_t STEP_INTERVAL_MS = 10;   // wall-clock rate (100 Hz)
static uint32_t lastStepMs = 0;

// -----------------------------------------------------------------------
// Print counter – print a header every N lines for readability
// -----------------------------------------------------------------------
static uint32_t printCount = 0;

#define LED_PIN 2 // Built-in LED on most ESP32 dev boards

// -----------------------------------------------------------------------
// Print aligned telemetry to Serial
// -----------------------------------------------------------------------
static void printTelemetry()
{
  // Access continuous states via the contStates pointer (set by initialize())
  auto *X = reinterpret_cast<VisionHelicopter::X_VisionHelicopter_T *>(
                rtm->contStates);
  if (!X) {
    Serial.println("[ERR] contStates null");
    return;
  }

  // --- State extraction ---
  double pitch_rad  = X->PlantPitch_CSTATE[0];     // Plant pitch angle (rad)
  double pitch_rate = X->PlantPitch_CSTATE[1];     // Plant pitch rate (rad/s)
  double roll_rad   = X->PlantRoll_CSTATE[0];      // Plant roll angle (rad)
  double roll_rate  = X->PlantRoll_CSTATE[1];      // Plant roll rate (rad/s)
  double altitude   = X->z_CSTATE[0];              // Altitude (m), +ve = up
  double alt_rate   = X->z_CSTATE[1];              // Vertical velocity (m/s)
  double vx         = X->vx_curr_CSTATE;           // Forward velocity (m/s)
  double vy         = X->Integrator1_CSTATE;       // Lateral velocity (m/s)

  // Convert to degrees
  double pitch_deg = pitch_rad * (180.0 / M_PI);
  double roll_deg  = roll_rad  * (180.0 / M_PI);

  // Velocity-based heading (proxy for yaw since model has no yaw dynamics)
  double speed_xy  = sqrt(vx * vx + vy * vy);
  double yaw_deg   = (speed_xy > 0.001) ? atan2(vy, vx) * (180.0 / M_PI) : 0.0;

  // Simulated time
  double simT = *(rtm->getTPtr());

  // Print header every 10 lines
  if (printCount % 10 == 0) {
    Serial.println();
    Serial.println("+--------+----------+----------+----------+-----------+----------+----------+----------+");
    Serial.println("| SimT   | Pitch    | Roll     | Yaw*     | Altitude  | AltRate  | Vx       | Vy       |");
    Serial.println("|  (s)   |  (deg)   |  (deg)   |  (deg)   |   (m)     |  (m/s)   |  (m/s)   |  (m/s)   |");
    Serial.println("+--------+----------+----------+----------+-----------+----------+----------+----------+");
  }
  printCount++;

  // Fixed-width row
  char buf[128];
  snprintf(buf, sizeof(buf),
    "| %6.1f | %+8.3f | %+8.3f | %+8.3f | %9.3f | %+8.3f | %+8.3f | %+8.3f |",
    simT, pitch_deg, roll_deg, yaw_deg, 
    altitude, alt_rate, vx, vy);
  Serial.println(buf);
}

// -----------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Try 115200
  delay(1000);
  Serial.println("\n[BAUD TEST] Testing at 115200...");
  
  // Try 9600
  Serial.updateBaudRate(9600);
  delay(500);
  Serial.println("\n[BAUD TEST] Testing at 9600...");
  
  // Try 74880 (ESP8266 default / ESP32 26MHz default)
  Serial.updateBaudRate(74880);
  delay(500);
  Serial.println("\n[BAUD TEST] Testing at 74880...");

  // Go back to 115200 for normal operation
  Serial.updateBaudRate(115200);
  delay(1000);

  Serial.println();
  Serial.println("============================================================");
  Serial.println("    VisionHelicopter Simulink Model  |  ESP32 Runtime");
  Serial.println("============================================================");
  Serial.println("  Model:  ERT target, ODE3 solver");
  Serial.println("  Step:   0.01 s / model step");
  Serial.println("  Alt setpoint: ~5 m   Vx setpoint: ~1 m/s");
  Serial.println("  * Yaw = velocity heading (no explicit yaw model)");
  Serial.println("============================================================");

  Serial.println("  Allocating model memory...");
  // Dynamically allocate to avoid global static initialization issues on ESP32
  model = new VisionHelicopter();

  if (model == nullptr) {
    Serial.println("[FATAL ERR] Failed to allocate memory for VisionHelicopter!");
    while (true) { delay(1000); }
  }

  Serial.println("  Initializing model...");
  // --- Initialize the Simulink model ---
  model->initialize();

  // --- Get the RT-model handle ---
  rtm = model->getRTM();

  // --- Wire the derivatives buffer ---
  // initialize() already sets rtm->derivs via rtsiSetdXPtr, but we
  // supply the actual backing buffer here (in case derivs is null/invalid).
  rtm->derivs = gDerBuf;
  // Re-sync the dXPtr so the ODE3 macro rtsiSetdX() writes into gDerBuf:
  rtm->solverInfo.dXPtr = &rtm->derivs;

  // --- Set continuous-state sizes ---
  rtm->Sizes.numContStates         = 20;
  rtm->Sizes.numPeriodicContStates = 0;

  // --- Check for model error ---
  const char *err = rtm->getErrorStatus();
  if (err) {
    Serial.print("[ERR] Model init failed: ");
    Serial.println(err);
    return;
  }

  Serial.println("  Model initialized OK.");
  Serial.println("  Starting simulation...");
  Serial.println();

  lastStepMs = millis();
}

// -----------------------------------------------------------------------
void loop()
{
  uint32_t now = millis();

  if ((now - lastStepMs) >= STEP_INTERVAL_MS) {
    lastStepMs = now;
    
    // Toggle LED to show activity
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));

    // Step the model (advances simulated time by 1.3 s)
    model->step();

    // Check for runtime errors
    const char *err = rtm->getErrorStatus();
    if (err) {
      Serial.print("[ERR] Runtime: ");
      Serial.println(err);
      delay(2000);
      return;
    }

    // Print telemetry at 10Hz (every 10th step)
    static uint32_t stepCount = 0;
    if (stepCount++ % 10 == 0) {
      printTelemetry();
    }
  }
}
