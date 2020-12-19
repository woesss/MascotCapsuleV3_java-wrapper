/*
 * Copyright (c) 2020. Yury Kharchenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

package ru.woesss.micro3d;

// dependency from target
import javax.microedition.lcdui.Graphics;

// dependency from FreeJ2ME
import org.recompile.mobile.PlatformGraphics;

import java.awt.image.DataBufferInt;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * Helper class for encapsulate target platform(s) specific code
 */
public class PlatformHelper {
	/** Name of class that loads resources of MIDlet in KEmulator 1.03 */
	public static final String RESOURCE_CLASS_NAME_KE103 = "emulator.custom.b";

	/** Name of class that loads resources of MIDlet in KEmulator 0.98 */
	public static final String RESOURCE_CLASS_NAME_KE098 = "emulator.custom.h";

	/** Name of class that loads resources of MIDlet in FreeJ2ME */
	public static final String RESOURCE_CLASS_NAME_FREEJ2ME = "org.recompile.mobile.Mobile";

	/** Resource loading method name in KEmulator */
	public static final String RESOURCE_METHOD_NAME_KE = "a";

	/** Resource loading method name in FreeJ2ME */
	public static final String RESOURCE_METHOD_NAME_FREEJ2ME = "getMIDletResourceAsStream";

	public static final int PLATFORM_FREEJ2ME = 1;
	public static final int PLATFORM_KE103 = 2;
	public static final int PLATFORM_KE098 = 3;

	private static Method getResourceMethod;
	private static int platform = -1;

	/**
	 * @param name resource name
	 * @return resource bytes
	 */
	public static byte[] getResourceBytes(String name) {
		if (getResourceMethod == null) {
			return null;
		}
		try {
			InputStream is = (InputStream) getResourceMethod.invoke(null, new String[] { name });
			if (is == null) {
				return null;
			}
			byte[] b = new byte[1024];
			int r;
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			try {
				while ((r = is.read(b)) != -1) {
					baos.write(b, 0, r);
				}
				final byte[] bytes = baos.toByteArray();
				if (bytes.length > 0) {
					return bytes;
				}
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				try {
					is.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return null;
	}

	/**
	 * @param graphics lcdui Graphics object bounded to 3D
	 * @return array for use as 3D buffer
	 */
	public static int[] getBuffer(Graphics graphics) {
		switch (platform) {
		case PLATFORM_FREEJ2ME:
			PlatformGraphics g = (PlatformGraphics) graphics;
			DataBufferInt dataBufferInt = (DataBufferInt) g.platformImage.getCanvas().getRaster().getDataBuffer();
			return dataBufferInt.getData();
		case PLATFORM_KE098:
		case PLATFORM_KE103:
			return graphics.getImage().getData();
		}
		return null;
	}

	public static int getWidth(Graphics graphics) {
		switch (platform) {
		case PLATFORM_FREEJ2ME:
			PlatformGraphics g = (PlatformGraphics) graphics;
			return g.platformImage.getWidth();
		case PLATFORM_KE098:
		case PLATFORM_KE103:
			return graphics.getImage().getWidth();
		}
		return -1;
	}

	public static int getHeight(Graphics graphics) {
		switch (platform) {
		case PLATFORM_FREEJ2ME:
			PlatformGraphics g = (PlatformGraphics) graphics;
			return g.platformImage.getHeight();
		case PLATFORM_KE098:
		case PLATFORM_KE103:
			return graphics.getImage().getHeight();
		}
		return -1;
	}

	static {
		Class clazz = null;
		try {
			clazz = Class.forName(RESOURCE_CLASS_NAME_KE103);
			platform = PLATFORM_KE103;
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		if (clazz == null) {
			try {
				clazz = Class.forName(RESOURCE_CLASS_NAME_KE098);
				platform = PLATFORM_KE098;
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}

		}
		if (clazz == null) {
			try {
				clazz = Class.forName(RESOURCE_CLASS_NAME_FREEJ2ME);
				platform = PLATFORM_FREEJ2ME;
				Method method = clazz.getDeclaredMethod(RESOURCE_METHOD_NAME_FREEJ2ME, new Class[] { String.class });
				method.setAccessible(true);
				getResourceMethod = method;
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			} catch (SecurityException e) {
				e.printStackTrace();
			}

		} else {
			final Method[] methods = clazz.getDeclaredMethods();
			for (int i = 0; i < methods.length; i++) {
				final Method method = methods[i];
				if (!method.getName().equals(RESOURCE_METHOD_NAME_KE)) {
					continue;
				}
				if (!method.getReturnType().equals(InputStream.class)) {
					continue;
				}
				final Class[] parameterTypes = method.getParameterTypes();
				if (parameterTypes.length != 1) {
					continue;
				}
				if (parameterTypes[0] != String.class) {
					continue;
				}
				method.setAccessible(true);
				getResourceMethod = method;
			}
		}
		if (platform == -1)
			System.err.println("Micro3D: unknown platform - You must add support it in this class!!!");
	}

	public static void onReleased(Graphics graphics) {
		switch (platform) {
		case PLATFORM_FREEJ2ME:
			PlatformGraphics g = (PlatformGraphics) graphics;
			DataBufferInt dataBufferInt = (DataBufferInt) g.platformImage.getCanvas().getRaster().getDataBuffer();
			int[] pixels = dataBufferInt.getData();
			for (int i = 0; i < pixels.length; i++) {
				pixels[i] |= 0xFF000000;
			}
			break;
		case PLATFORM_KE098:
		case PLATFORM_KE103:
		}
	}
}
