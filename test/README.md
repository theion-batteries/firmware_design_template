# Tests


test id | purpose | type | result  |
| :-------------: | :-------------: |:-------------:| -----:|
|command_id| send "id" and receive specific device id | unit | pass  |
|state_id| after succeful identification the state manager switch to ready state | unit | pass  |
|parseOnce_id| id command could be parsed only once at the beginning | unit | pass  |
|command_home| send "home" and return ok if homed | unit | pass  |
|state_homing| once home command received, state switch from ready to homing until it is homed, then back to ready | unit | pass  |
|parceMulti_home| home command can be parsed many times, as long as previous state was ready| unit | pass  |
|command_align| send "align" and return ok if aligned | unit | pass  |
|state_align| once align command received, state switch from ready to aligning until it is aligned, then back to ready | unit | pass  |
|parceMulti_align| align command can be parsed many times, as long as previous state was ready| unit | pass  |
|emegency_button| press emegency button to urgently break current state/command and return it to ready | integration | pass  |
|command_break| send break command to urgently break current state/command and return it to ready | integration | failed  |
|command_upAllMax| send "upAllMax" and return ok if allUpMax | unit | pass  |
|command_upXMax| send "upXMax" and return ok if xUpMax | unit | pass  |
|command_upYMax| send "upYMax" and return ok if yUpMax | unit | pass  |
|command_upZMax| send "upZMax" and return ok if zUpMax | unit | pass  |
|command_downAllMax| send "downAllMax" and return ok if allDownMax | unit | pass  |
|command_downXMax| send "downXMax" and return ok if xDownMax | unit | pass  |
|command_downYMax| send "downYMax" and return ok if yDownMax | unit | pass  |
|command_downZMax| send "downZMax" and return ok if zDownMax | unit | pass  |
|command_upAll| send "upAll+distance" and return ok if allUpDistanceArrived | unit | pass  |
|command_upX| send "upX+distance" and return ok if xUpDistanceArrived | unit | pass  |
|command_upY| send "upY+distance" and return ok if yUpDistanceArrived | unit | pass  |
|command_upZ| send "upZ+distance" and return ok if zUpDistanceArrived | unit | pass  |
|command_downAll| send "downAll+distance" and return ok if allDownDistanceArrived | unit | pass  |
|command_downX| send "downX+distance" and return ok if xDownDistanceArrived | unit | pass  |
|command_downY| send "downY+distance" and return ok if yDownDistanceArrived | unit | pass  |
|command_downZ| send "downZ+distance" and return ok if zDownDistanceArrived | unit | pass  |
