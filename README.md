# topside-2

Software for topside controller using ROS 2.

## Controller Mappings

These mappings only work if the controller is in 'X' mode (switch on the back of the controller)

|    Button     |             Function              |
| :-----------: | :-------------------------------: |
|     Start     |            Arm Motors             |
|     Back      |           Disarm Motors           |
| Left Stick X  |           Left / Right            |
| Left Stick Y  |         Forward / Reverse         |
| Right Stick X |      Turn Left / Turn Right       |
| Right Stick Y |             Up / Down             |
| Left Trigger  |             Open Claw             |
| Right Trigger |            Close Claw             |
|     X / B     |         Cycle Cameras (?)         |
|       Y       | Enable / Disable Control Loop (?) |

Might be worth trying to make the buttons configurable with a file. I would have attempted it if C++ had reflection but unfortunately that won't be happening until C++26 at the earliest.
