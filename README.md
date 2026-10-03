#**Laboratory Activity 4: Analog Input, PWM, and DAC**

**Hardware used:** Examples 3 and 4 were run on an ESP32-S3 Dev Module (potentiometer on GPIO4, LED on GPIO5). Example 5 (DAC) was run on an original ESP32 (DAC output on GPIO25), since the ESP32-S3 has no DAC.

***Table 1:*** *Potentiometer readings* (Board: ESP32-S3)

+-------------------+------+-----------------+---------------------+
| Knob Position (%) | Raw  | Millivolts (mV) | Expected (ideal, V) |
+-------------------+------+-----------------+---------------------+
|                 0 |    0 |             142 |               0.000 |
|                25 | 1025 |             945 |               0.826 |
|                50 | 2046 |            1750 |               1.649 |
|                75 | 3072 |            2543 |               2.476 |
|               100 | 4095 |            3112 |               3.300 |
+-------------------+------+-----------------+---------------------+

Expected = raw / 4095 × 3.3 V.

***Table 2:*** *PWM duty* (Board: ESP32-S3)

+-------------------+------+------------------+-----------------+---------------+
| Knob Position (%) | Raw  | Predicted (calc) | Predicted (int) | Observed duty |
+-------------------+------+------------------+-----------------+---------------+
|                 0 |    0 |             0.00 |               0 |             0 |
|                25 | 1023 |            63.70 |              63 |            63 |
|                50 | 2047 |           127.47 |             127 |           127 |
|                75 | 3071 |           191.23 |             191 |           191 |
|               100 | 4095 |           255.00 |             255 |           255 |
+-------------------+------+------------------+-----------------+---------------+

Predicted = raw × 255 / 4095. The raw values differ from Table 1 because this was a separate run with the knob positioned by eye.

***Table 3:*** *DAC voltage* (Board: original ESP32, GPIO25, multimeter)

+----------+----------------+--------------+----------+
| DAC code | Calculated (V) | Measured (V) | Diff (V) |
+----------+----------------+--------------+----------+
|        0 |           0.00 |         0.00 |     0.00 |
|       64 |           0.83 |         0.82 |    -0.01 |
|      128 |           1.66 |         1.64 |    -0.02 |
|      192 |           2.48 |         2.45 |    -0.03 |
|      255 |           3.30 |         3.30 |     0.00 |
+----------+----------------+--------------+----------+

Calculated = code / 255 × 3.3 V. Diff = Measured − Calculated.

**Comparison of predicted and observed results**

**-ADC (Table 1):** 

The raw code and millivolt readings increased with knob position. They did not match the ideal linear values exactly: there was an offset at 0% (142 mV instead of 0 V), and the 100% reading was 3112 mV instead of 3300 mV. Raw and millivolt values come from two separate conversions, so they need not correspond exactly.

**-PWM (Table 2):** 

Observed duty matched the integer prediction at all five positions. The duty is calculated from the raw reading using map(), which uses integer arithmetic and rounds down. For example, raw 1023 gives 63 rather than 64. Because duty depends on the raw code and not on measured voltage, the ADC offset and saturation do not change the predicted-versus-observed comparison.

**=DAC (Table 3):** 

Measured voltages increased steadily with the DAC code and were within 0.03 V of the calculated values. The small differences are expected because the ESP32 DAC output range is not exactly 0 to 3.3 V, and the board supply and multimeter have their own tolerance.

***PWM vs DAC:** PWM is a digital signal that switches repeatedly between LOW (0 V) and HIGH (3.3 V). The duty cycle sets the fraction of each cycle spent HIGH. At 5 kHz, one cycle lasts 200 µs. A multimeter may show an average voltage, but the waveform is still switching. The DAC outputs a steady analog voltage set by the code (0–255), with no switching. Similar meter readings do not make them the same signal, so the PWM results in Table 2 are not DAC measurements.

**Sketches submitted:**

Example 3 (ADC, S3 version, pin 4), Example 4 (PWM, S3 version, pins 4 and 5), Example 5 (DAC, original ESP32, GPIO25).
