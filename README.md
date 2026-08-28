# Pi Zero Rover

## Project Goal

Build a battery-powered rover from scratch, with chassis, electronics, and all software written in C. Controllable remotely via live camera feed, exposed over the internet through self-hosting.

Learning goals: embedded software, Linux, GPIO, autonomous systems, computer vision, camera.

---

## Hardware

### Owned

| Component                       | Details                                                          | Status |
| ------------------------------- | ---------------------------------------------------------------- | ------ |
| Raspberry Pi Camera Module V2   | Official, IMX219 sensor, 8MP, 1080p, CSI                         | +      |
| MakerSpot Zero Camera Cable Set | 1.6" / 3.2" / 5.9" ribbon flex, Zero-compatible 22-pin           | +      |
| TT Gear Motors x4               | SazkJere, 3-6V DC, 200RPM, 1:48 gearbox, dual shaft, 200mm wired | +      |
| L298N Motor Driver x3           | Dual H-bridge, handles 2A per channel                            | +      |
| 4xAA Battery Holder x2          | With leads and wires, motor power supply                         | +      |
| M3 Screw/Nut Kit                | For chassis mounting                                             | +      |
| Jumper Wires                    | M-M and M-F                                                      | +      |
| 3D Printer                      | Chassis fabrication                                              | +      |
| Raspberry Pi Zero 2 WH          | Main compute board, pre-soldered headers                         | +      |

### To Buy

| Component                        | Purpose              | Priority |
| -------------------------------- | -------------------- | -------- |
| MicroSD Card (32GB, A1/Class 10) | OS + project storage | Phase 2  |
| 4xAA Batteries                   | Motor power          | Phase 1  |

### Power Architecture

Two separate power rails for development. Motor noise or voltage sag on a shared rail might corrupt the Pi.

Motors -> 4×AA battery holder (6V nominal)
Pi -> USB from laptop

Pi battery power is deferred to Phase 5.

---

## Software Stack

All software written in C.

TBD

---

## Phases

### Phase 0: Hardware : +

Identify and source all components.

### Phase 1: Motor control : WIP

Desc: Get motors working on the Pi. Validate GPIO and PWM (Pulse Width Modulation).

Deliverable: C program that drives one TT motor forward, backward, and stop, using PWM for speed control via the L298N driver.

### Phase 2: Camera streaming

Desc: Get the Camera Module V2 capturing frames and streaming over the local network. Validate the CSI -> libcamera -> encode -> serve pipeline in C.

Deliverable: MJPEG stream viewable in a browser on the same WiFi network.

### Phase 3: Control server : WIP

Desc: Accept movement commands over a TCP socket. Translate commands to motor signals.

Deliverable: C server accepting FORWARD / BACK / LEFT / RIGHT / STOP over TCP, driving motors accordingly.

### Phase 4: Integration

Desc: Combine Phase 2 and Phase 3. Drive the rover while watching the camera feed. Expose both over the internet by self-hosting.

Deliverable: Browser-accessible interface showing live camera feed with real-time drive controls.

### Phase 5: Chassis : WIP

Desc: Design and 3D print the chassis.

Deliverable: A chassis

### Phase 6: Wrap up

Desc: Mount all validated electronics. Solve untethered Pi power.

Deliverable: A physical rover driving on its own power with no cables.

## Resources:

- https://www.youtube.com/watch?v=BXBlYpxT4tw
- [L298N Motor Driver Datasheet](https://www.st.com/resource/en/datasheet/l298.pdf)
- [libgpiod Documentation](https://libgpiod.readthedocs.io/)
- [libcamera C API](https://libcamera.org/api-html/)
