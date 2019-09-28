package com.waltmoorhouse.jni.rpi.ws2811;

import javax.annotation.PreDestroy;

/**
 * Basic class to interface with the rpi_ws281x native library
 */
public class RaspberryPiWs2811LedStripJNI {
	private int stripId = -1;
	private boolean clearOnExit = false;
	/**
	 * Default constructor with the following settings:
	 * <ul>
	 * <li>ledCount = 100</li>
	 * <li>gpioPin = 18</li>
	 * <li>frequenchHz = 800000</li>
	 * <li>dma = 10</li>
	 * <li>brightness = 255</li>
	 * <li>pwmChannel = 0</li>
	 * <li>invert = false</li>
	 * </ul>
	 */
	public RaspberryPiWs2811LedStripJNI() {
		String ret = addStrip(
				"GRB",
				30,
				18,
				800000,
				10,
				255,
				0,
				false
		);
		try {
			stripId = Integer.parseInt(ret);
		} catch (NumberFormatException e) {
			throw new ExceptionInInitializerError(ret);
		}
	}

	/**
	 * Create an LED strip with the given settings
	 *
	 * @param stripType   RGB, GBR, RGBW, etc.
	 * @param ledsCount   The number of LEDs in the strip
	 * @param gpioPin     The Raspberry Pi GPIO pin
	 * @param frequencyHz Frequency of updates in Hertz
	 * @param dma         DMA to use
	 * @param brightness  Starting brightness for colors
	 * @param pwmChannel  PWM Channel to use
	 * @param invert      Whether or not to invert color values
	 */
	public RaspberryPiWs2811LedStripJNI(String stripType, int ledsCount, int gpioPin, int frequencyHz, int dma, int brightness, int pwmChannel, boolean invert, boolean clearOnExit) {  //NOSONAR
		this.clearOnExit = clearOnExit;
		String ret = addStrip(stripType, ledsCount, gpioPin, frequencyHz, dma, brightness, pwmChannel, invert);
		try {
			stripId = Integer.parseInt(ret);
		} catch (NumberFormatException e) {
			throw new ExceptionInInitializerError(ret);
		}
	}

	private native String addStrip(String stripType, int ledsCount, int gpioPin, int frequencyHz, int dma, int brightness, int pwmChannel, boolean invert); //NOSONAR

	/**
	 * Sets an individual pixel to an html color code. Do not send the '#' prefix
	 *
	 * @param pixel pixel location in strip
	 * @param rgbHex 6 character 0 filled hex, so white is ffffff, red is ff0000, green is 00ff00, blue is 0000ff, etc.
	 */
	public void setPixel(int pixel, String rgbHex) {
		setPixel(stripId, pixel, rgbHex);
	}

	private native void setPixel(int stripId, int pixel, String rgbHex);

	/**
	 * Set the color of an individual pixel
	 *
	 * @param pixel The index of the pixel in the strip
	 * @param red The red value (0 - 255)
	 * @param green The green value (0 - 255)
	 * @param blue The blue value (0 - 255)
	 */
	public void setPixel(int pixel, int red, int green, int blue) {
		setPixel(stripId, pixel, red, green, blue);
	}

	private native void setPixel(int stripId, int pixel, int red, int green, int blue);

	/**
	 * Sets the entire strip to an html color code. Do not send the '#' prefix.
	 *
	 * @param rgbHex 6 character 0 filled hex, so white is ffffff, red is ff0000, green is 00ff00, blue is 0000ff, etc.
	 */
	public void setStrip(String rgbHex) {
		setStrip(stripId, rgbHex);
	}

	private native void setStrip(int stripId, String rgbHex);

	/**
	 * Set all LEDs in the strip to one color
	 *
	 * @param red The red value (0 - 255)
	 * @param green The green value (0 - 255)
	 * @param blue The blue value (0 - 255)
	 */
	public void setStrip(int red, int green, int blue) {
		setStrip(stripId, red, green, blue);
	}

	private native void setStrip(int stripId, int red, int green, int blue);

	/**
	 * Render the current values to the physical light strip.
	 *
	 * This method needs to be called after any previous setPixel calls to make the lights change to those colors.
	 */
	public String render() {
		return render(stripId);
	}

	private native String render(int stripId);

	/**
	 * Clears the string, turning off all leds
	 *
	 * @return
	 */
	public String clear() {
		return clear(stripId);
	}

	private native String clear(int stripId);

	/**
	 * Disconnect from LED strip and cleanup resources on native side.
	 */
	public void disconnect() {
		disconnect(stripId);
	}

	private native void disconnect(int stripId);

	@PreDestroy
	public void shutdown() {
		if (clearOnExit) {
			clear(stripId);
		}
		disconnect();
	}
}
