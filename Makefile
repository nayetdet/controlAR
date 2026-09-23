.PHONY: run build upload monitor reset clean

ENV ?= esp32dev
BAUD_RATE ?= 115200

run: upload monitor

build:
	pio run -e $(ENV)

upload:
	pio run -e $(ENV) -t upload

monitor:
	pio device monitor -b $(BAUD_RATE)

reset:
	pio run -e $(ENV) -t reset
	$(MAKE) monitor

clean:
	pio run -e $(ENV) -t clean

preprocess-video:
	bash tools/preprocess_video.sh video.webm video.rgb565 audio.pcm
