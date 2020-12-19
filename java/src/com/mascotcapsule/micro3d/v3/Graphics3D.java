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

package com.mascotcapsule.micro3d.v3;

import javax.microedition.lcdui.Graphics;

import ru.woesss.micro3d.PlatformHelper;

public class Graphics3D {
	public static final int COMMAND_LIST_VERSION_1_0 = -33554431;
	public static final int COMMAND_END = -2147483648;
	public static final int COMMAND_NOP = -2130706432;
	public static final int COMMAND_FLUSH = -2113929216;
	public static final int COMMAND_ATTRIBUTE = -2097152000;
	public static final int COMMAND_CLIP = -2080374784;
	public static final int COMMAND_CENTER = -2063597568;
	public static final int COMMAND_TEXTURE_INDEX = -2046820352;
	public static final int COMMAND_AFFINE_INDEX = -2030043136;
	public static final int COMMAND_PARALLEL_SCALE = -1879048192;
	public static final int COMMAND_PARALLEL_SIZE = -1862270976;
	public static final int COMMAND_PERSPECTIVE_FOV = -1845493760;
	public static final int COMMAND_PERSPECTIVE_WH = -1828716544;
	public static final int COMMAND_AMBIENT_LIGHT = -1610612736;
	public static final int COMMAND_DIRECTION_LIGHT = -1593835520;
	public static final int COMMAND_THRESHOLD = -1358954496;
	public static final int PRIMITVE_POINTS = 16777216;
	public static final int PRIMITVE_LINES = 33554432;
	public static final int PRIMITVE_TRIANGLES = 50331648;
	public static final int PRIMITVE_QUADS = 67108864;
	public static final int PRIMITVE_POINT_SPRITES = 83886080;
	public static final int POINT_SPRITE_LOCAL_SIZE = 0;
	public static final int POINT_SPRITE_PIXEL_SIZE = 1;
	public static final int POINT_SPRITE_PERSPECTIVE = 0;
	public static final int POINT_SPRITE_NO_PERS = 2;
	public static final int ENV_ATTR_LIGHTING = 1;
	public static final int ENV_ATTR_SPHERE_MAP = 2;
	public static final int ENV_ATTR_TOON_SHADING = 4;
	public static final int ENV_ATTR_SEMI_TRANSPARENT = 8;
	public static final int PATTR_LIGHTING = 1;
	public static final int PATTR_SPHERE_MAP = 2;
	public static final int PATTR_COLORKEY = 16;
	public static final int PATTR_BLEND_NORMAL = 0;
	public static final int PATTR_BLEND_HALF = 32;
	public static final int PATTR_BLEND_ADD = 64;
	public static final int PATTR_BLEND_SUB = 96;
	public static final int PDATA_NORMAL_NONE = 0;
	public static final int PDATA_NORMAL_PER_FACE = 512;
	public static final int PDATA_NORMAL_PER_VERTEX = 768;
	public static final int PDATA_COLOR_NONE = 0;
	public static final int PDATA_COLOR_PER_COMMAND = 1024;
	public static final int PDATA_COLOR_PER_FACE = 2048;
	public static final int PDATA_TEXURE_COORD_NONE = 0;
	public static final int PDATA_POINT_SPRITE_PARAMS_PER_CMD = 4096;
	public static final int PDATA_POINT_SPRITE_PARAMS_PER_FACE = 8192;
	public static final int PDATA_POINT_SPRITE_PARAMS_PER_VERTEX = 12288;
	public static final int PDATA_TEXURE_COORD = 12288;

	private int nPointer;
	private int nBufPointer;
	private boolean isBound = false;
	private Graphics mGraphics;
	private int[] mBuffer;

	public Graphics3D() {
		nPointer = nInit();
		if (nPointer == 0) {
			throw new RuntimeException();
		}
	}

	public final synchronized void bind(Graphics graphics) {
		if (isBound) {
			throw new IllegalStateException("Target already bound");
		}
		mGraphics = graphics;
		int width = PlatformHelper.getWidth(graphics);
		int height = PlatformHelper.getHeight(graphics);
		int cx = graphics.getClipX() + graphics.getTranslateX();
		int cy = graphics.getClipY() + graphics.getTranslateY();
		int cw = graphics.getClipWidth();
		int ch = graphics.getClipHeight();
		if (mBuffer == null || mBuffer.length != width * height)
			mBuffer = new int[width * height];
		nBind(mBuffer, width, height, cx, cy, cw, ch);
		isBound = true;
	}

	public final void dispose() {
		if (nPointer != 0) {
			nFinalize();
			nPointer = 0;
		}
	}

	public final synchronized void drawCommandList(Texture[] textures, int x, int y, FigureLayout layout,
									  Effect3D effect, int[] commandList) {
		if (layout == null || effect == null) {
			throw new NullPointerException();
		}
		if (textures != null) {
			for (int i = 0; i < textures.length; ++i) {
				Texture tex = textures[i];
				if (tex == null) {
					throw new NullPointerException();
				}
				if (tex.nPointer == 0) {
					throw new RuntimeException("Already disposed");
				}
			}
		}
	
		if (commandList == null) {
			throw new NullPointerException();
		}
	
		int[] buffer = (int[]) PlatformHelper.getBuffer(mGraphics);
		nCapture(buffer);
		int ret = nDrawCmd(textures, x, y, layout, effect, commandList);
		if (ret == -1) {
			throw new RuntimeException();
		}
		if (ret != 0) {
			throw new IllegalArgumentException();
		}
		nRender(buffer);
	}

	public final void drawCommandList(Texture texture, int x, int y, FigureLayout layout,
									  Effect3D effect, int[] commandList) {
		Texture[] ta = null;
		if (texture != null) {
			ta = new Texture[]{texture};
		}
	
		drawCommandList(ta, x, y, layout, effect, commandList);
	}

	public final synchronized void drawFigure(Figure figure, int x, int y, FigureLayout layout, Effect3D effect) {
		checkTargetIsValid();
		if (figure == null || layout == null || effect == null) {
			throw new NullPointerException();
		}
		if (nPointer == 0) {
			throw new RuntimeException("Already disposed");
		}

		
		int[] buffer = (int[]) PlatformHelper.getBuffer(mGraphics);
		nCapture(buffer);
		int ret = nDrawFigure(figure, x, y, layout, effect);
		if (ret == -1) {
			throw new RuntimeException();
		}
		if (ret != 0) {
			throw new IllegalArgumentException();
		}
		nRender(buffer);
	}

	public final synchronized void flush() {
		checkTargetIsValid();

		int[] buffer = (int[]) PlatformHelper.getBuffer(mGraphics);
		nCapture(buffer);
		int ret = nFlush();
		if (ret != 0) {
			throw new RuntimeException();
		}
		nRender(buffer);
	}

	public final synchronized void release(Graphics graphics) {
		if (!isBound) {
			return;
		}
		if (graphics != mGraphics) {
			throw new IllegalArgumentException("Unknown target");
		}

		nRelease(mBuffer);
		PlatformHelper.onReleased(graphics);
		mGraphics = null;
		isBound = false;
	}

	public final synchronized void renderFigure(Figure figure, int x, int y, FigureLayout layout, Effect3D effect) {
		checkTargetIsValid();
		if (figure == null || layout == null || effect == null) {
			throw new NullPointerException();
		}
		if (nPointer == 0) {
			throw new RuntimeException("Already disposed");
		}
		int ret = nRenderFigure(figure, x, y, layout, effect);
		if (ret == -1) {
			throw new RuntimeException();
		}
		if (ret != 0) {
			throw new IllegalArgumentException();
		}
	}

	public final synchronized void renderPrimitives(Texture texture, int x, int y, FigureLayout layout, Effect3D effect,
									   int command, int numPrimitives, int[] vertexCoords, int[] normals,
									   int[] textureCoords, int[] colors) {
		if (layout == null || effect == null) {
			throw new NullPointerException();
		}
		if (vertexCoords == null || normals == null || textureCoords == null || colors == null) {
			throw new NullPointerException();
		}
		if (command < 0) {
			throw new IllegalArgumentException();
		}
		if (numPrimitives <= 0 || numPrimitives > 255) {
			throw new IllegalArgumentException();
		}
		if (texture != null && texture.nPointer == 0) {
			throw new RuntimeException("Already disposed");
		}
		int ret = nRenderPrimitive(texture, x, y, layout, effect, command | numPrimitives << 16,
				vertexCoords, normals, textureCoords, colors);
		if (ret == -1) {
			throw new RuntimeException();
		}
		if (ret != 0) {
			throw new IllegalArgumentException();
		}
	}

	private void checkTargetIsValid() {
		if (mGraphics == null) {
			throw new IllegalStateException("No target is bound");
		}
	}

	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}

	private native int  nInit();
	private native void nBind(int[] buf, int w, int h, int cx, int cy, int cw, int ch);
	private native void nCapture(int[] buffer);
	private native void nRender(int[] buffer);
	private native int  nDrawCmd(Texture[] ta, int x, int y, FigureLayout layout, Effect3D effect, int[] cmds);
	private native int  nDrawFigure(Figure f, int x, int y, FigureLayout l, Effect3D e);
	private native int  nRenderPrimitive(Texture tex, int x, int y, FigureLayout layout, Effect3D effect, int c,
								   int[] coords, int[] normals, int[] texCoord, int[] colors);
	private native int  nRenderFigure(Figure f, int x, int y, FigureLayout l, Effect3D e);
	private native int  nFlush();
	private native void nRelease(int[] buffer);
	private native void nFinalize();

	private static native void nInitClass();

	static {
		System.loadLibrary("java_micro3d_v3_32");
		nInitClass();
	}
}
