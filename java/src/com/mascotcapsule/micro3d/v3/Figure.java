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

import java.io.IOException;

import ru.woesss.micro3d.PlatformHelper;

public class Figure {
	private int nPointer;
	private Texture mTexture;
	private Texture[] mTexArray;

	public Figure(byte[] b) {
		if (b == null) {
			throw new NullPointerException("Argument is null");
		}
		nPointer = nInit(b);
		if (nPointer == 0) {
			throw new RuntimeException();
		}
	}

	public Figure(String name) throws IOException {
		if (name == null) {
			throw new NullPointerException("Argument is null");
		}
		byte[] b = PlatformHelper.getResourceBytes(name);
		if (b == null) {
			throw new IOException("Resource \"" + name + "\" not found");
		}
		nPointer = nInit(b);
		if (nPointer == 0) {
			throw new RuntimeException();
		}
	}

	public final int getNumPattern() {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		return nGetNumPatterns();
	}

	public final int getNumTextures() {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		return mTexArray == null ? 0 : mTexArray.length;
	}

	public final Texture getTexture() {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		return mTexture;
	}

	public final void selectTexture(int idx) {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		if (mTexArray == null || idx < 0 || idx >= mTexArray.length) {
			throw new IllegalArgumentException();
		}
		Texture tex = mTexArray[idx];
		if (tex.nPointer == 0) {
			throw new RuntimeException("Texture is disposed");
		}
		mTexture = tex;
	}

	public final void setPattern(int idx) {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		nSetPattern(idx);
	}

	public final void setPosture(ActionTable act, int action, int frame) {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		if (act == null) {
			throw new NullPointerException("Argument ActionTable is null");
		}
		if (action < 0 || action >= act.getNumActions()) {
			throw new IllegalArgumentException("Illegal action index: " + action);
		}
		nSetPosture(act, action, frame);
	}

	public final void setTexture(Texture t) {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		if (t == null) {
			throw new NullPointerException("Argument is null");
		}
		if (t.nPointer == 0) {
			throw new RuntimeException("Texture is disposed");
		}
		if (!t.isForModel) {
			throw new IllegalArgumentException("Texture not for model");
		}
		mTexArray = new Texture[1];
		mTexArray[0] = t;
		mTexture = t;
	}

	public final void setTexture(Texture[] t) {
		if (nPointer == 0) {
			throw new RuntimeException("Figure is disposed");
		}
		if (t == null) {
			throw new NullPointerException("Argument is null");
		}
		if (t.length == 0) {
			throw new IllegalArgumentException("Array is empty");
		}
		for (int i = 0; i < t.length; ++i) {
			if (t[i] == null) {
				throw new NullPointerException("Null element at index=" + i);
			}
		
			if (t[i].nPointer == 0) {
				throw new RuntimeException("Disposed texture at index=" + i);
			}
		
			if (!t[i].isForModel) {
				throw new IllegalArgumentException("Texture not for model at index=" + i);
			}
		}
		
		mTexArray = t;
		mTexture = null;
	}

	public final void dispose() {
		if (nPointer != 0) {
			nFinalize();
			nPointer = 0;
		}
	}

	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}

	private native int nInit(byte[] b);
	private native void nSetPosture(ActionTable a, int i, int f);
	private native void nSetPattern(int p);
	private native int nGetNumPatterns();
	private native void nFinalize();

	private static native void nInitClass();

	static {
		System.loadLibrary("java_micro3d_v3_32");
		nInitClass();
	}
}
