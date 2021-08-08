# Wio link personal custom code (with PlatformIO)

- Install PlatformIO-cli (should be in `/home/hoel/.platformio/penv/bin/platformio`).
- Have the `Wio_link.sublime-project` file loaded in subl, or re-create it with `pio project init --ide sublimetext`.
- In sublime-text: `Menu > Tools > Build System > PlatformIO`, then build or upload.
- For serial monitor: `/home/hoel/.platformio/penv/bin/platformio device monitor -b 115200`.


Interesting links:
- https://github.com/Seeed-Studio/Wio_Link/wiki/Advanced-User-Guide#6-use-wio-link-offline
