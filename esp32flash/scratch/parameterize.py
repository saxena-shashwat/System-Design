import re

cpp_file = r'c:\Users\Naman Sinha\Desktop\System-Design\esp32flash\lib\VisionHelicopter\src\VisionHelicopter.cpp'
h_file = r'c:\Users\Naman Sinha\Desktop\System-Design\esp32flash\lib\VisionHelicopter\include\VisionHelicopter.h'

with open(cpp_file, 'r') as f:
    cpp_lines = f.readlines()

with open(h_file, 'r') as f:
    h_code = f.read()

# First replace the hardcoded ++ for Vx reference
for i in range(len(cpp_lines)):
    if '_rtXdot->LowPassFilter_CSTATE_d++;' in cpp_lines[i]:
        cpp_lines[i] = cpp_lines[i].replace('_rtXdot->LowPassFilter_CSTATE_d++;', '_rtXdot->LowPassFilter_CSTATE_d += VisionHelicopter_P.Vx_LowPass_Input;')

replacements = {
    '0.83333333333333337': 'VisionHelicopter_P.LowPass_Filter_Coef',
    '7.0711': 'VisionHelicopter_P.PitchRoll_Kp',
    '-1.1909': 'VisionHelicopter_P.PitchRoll_Kd',
    '3.0': 'VisionHelicopter_P.RateLimit_Rise',
    '-3.0': 'VisionHelicopter_P.RateLimit_Fall',
    '1.5': 'VisionHelicopter_P.Sat_Upper',
    '-1.5': 'VisionHelicopter_P.Sat_Lower',
    '5.0': 'VisionHelicopter_P.Integrator_Upper',
    '-5.0': 'VisionHelicopter_P.Integrator_Lower',
    '100.0': 'VisionHelicopter_P.Filter_Coef',
    '2.0': 'VisionHelicopter_P.Alt_Filter_Coef',
    '10.0': 'VisionHelicopter_P.Alt_LowPass_Input',
    '-10000.0': 'VisionHelicopter_P.Thrust_Transfer_Gain',
    '9.81': 'VisionHelicopter_P.Gravity',
    '0.75': 'VisionHelicopter_P.Thrust_Base_Gain',
    '60.0': 'VisionHelicopter_P.Thrust_Rate_Rise',
    '-60.0': 'VisionHelicopter_P.Thrust_Rate_Fall',
    '20.0': 'VisionHelicopter_P.Thrust_Sat_Upper',
    '0.5': 'VisionHelicopter_P.Drag_Coef',
    '0.87266': 'VisionHelicopter_P.Pitch_Sat_Upper',
    '-0.87266': 'VisionHelicopter_P.Pitch_Sat_Lower',
    '14.715': 'VisionHelicopter_P.Hover_Thrust',
    '32.0': 'VisionHelicopter_P.Plant_Actuator_Gain'
}

def replace_tokens(line):
    for num, repl in replacements.items():
        pattern = r'(?<![a-zA-Z0-9_.])' + re.escape(num) + r'(?![a-zA-Z0-9_.])'
        line = re.sub(pattern, repl, line)
    return line

for i in range(len(cpp_lines)):
    if 27 <= i <= 112:
        continue
    cpp_lines[i] = replace_tokens(cpp_lines[i])

struct_def = """
  // Tunable parameters
  struct P_VisionHelicopter_T {
    real_T LowPass_Filter_Coef = 0.83333333333333337;
    real_T PitchRoll_Kp = 7.0711;
    real_T PitchRoll_Kd = -1.1909;
    real_T RateLimit_Rise = 3.0;
    real_T RateLimit_Fall = -3.0;
    real_T Sat_Upper = 1.5;
    real_T Sat_Lower = -1.5;
    real_T Integrator_Upper = 5.0;
    real_T Integrator_Lower = -5.0;
    real_T Filter_Coef = 100.0;
    real_T Alt_Filter_Coef = 2.0;
    real_T Alt_LowPass_Input = 5.0; // For 5m alt setpoint, DC gain = 10/2 = 5
    real_T Vx_LowPass_Input = 0.0;  // Exposed Vx reference input
    real_T Thrust_Transfer_Gain = -10000.0;
    real_T Gravity = 9.81;
    real_T Thrust_Base_Gain = 0.75;
    real_T Thrust_Rate_Rise = 60.0;
    real_T Thrust_Rate_Fall = -60.0;
    real_T Thrust_Sat_Upper = 20.0;
    real_T Drag_Coef = 0.5;
    real_T Pitch_Sat_Upper = 0.087266; // Changed from 0.87266 (50 deg) to 5 deg
    real_T Pitch_Sat_Lower = -0.087266; // Changed from -0.87266 to -5 deg
    real_T Hover_Thrust = 14.715;
    real_T Plant_Actuator_Gain = 32.0;
  };

  P_VisionHelicopter_T VisionHelicopter_P;
"""

if 'struct DW_VisionHelicopter_T {' in h_code and 'struct P_VisionHelicopter_T' not in h_code:
    h_code = h_code.replace('struct DW_VisionHelicopter_T {', struct_def + '\n  struct DW_VisionHelicopter_T {')
elif 'struct P_VisionHelicopter_T' in h_code:
    # already parameterized, replace it
    h_code = re.sub(r'struct P_VisionHelicopter_T \{.*?\};\n\n  P_VisionHelicopter_T VisionHelicopter_P;', struct_def.strip(), h_code, flags=re.DOTALL)

with open(cpp_file, 'w') as f:
    f.writelines(cpp_lines)

with open(h_file, 'w') as f:
    f.write(h_code)

print("Replacement complete.")
