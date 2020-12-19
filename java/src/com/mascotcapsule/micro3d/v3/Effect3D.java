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

public class Effect3D {
	public static final int NORMAL_SHADING = 0;
	public static final int TOON_SHADING   = 1;

	private boolean isBlendEnable;
	private int mShading;
	private int mHigh;
	private int mLow;
	private int mThreshold;
	private Light mLight;
	private Texture mTexture;

	public Effect3D() {
	}

	public Effect3D(Light light, int shading, boolean isEnableTrans, Texture tex) {
		if (shading != 0 && shading != 1) {
			throw new IllegalArgumentException();
		}
		if (tex != null) {
			if (tex.isForModel) {
				throw new IllegalArgumentException();
			}

			if (tex.nPointer == 0) {
				throw new RuntimeException("Texture already disposed");
			}
		}

		mLight = light;
		mShading = shading;
		isBlendEnable = isEnableTrans;
		mTexture = tex;
	}

	public final Light getLight() {
		return mLight;
	}

	public final int getShading() {
		return mShading;
	}

	public final int getShadingType() {
		return mShading;
	}

	public final Texture getSphereMap() {
		return mTexture;
	}

	public final Texture getSphereTexture() {
		return mTexture;
	}

	public final int getThreshold() {
		return mThreshold;
	}

	public final int getThresholdHigh() {
		return mHigh;
	}

	public final int getThresholdLow() {
		return mLow;
	}

	public final int getToonHigh() {
		return mHigh;
	}

	public final int getToonLow() {
		return mLow;
	}

	public final int getToonThreshold() {
		return mThreshold;
	}

	public final boolean isSemiTransparentEnabled() {
		return isBlendEnable;
	}

	public final boolean isTransparency() {
		return isBlendEnable;
	}

	public final void setLight(Light light) {
		mLight = light;
	}

	public final void setSemiTransparentEnabled(boolean isEnable) {
		isBlendEnable = isEnable;
	}

	public final void setShading(int shading) {
		setShadingType(shading);
	}

	public final void setShadingType(int shading) {
		if (shading != 0 && shading != 1) {
			throw new IllegalArgumentException();
		}
		mShading = shading;
	}

	public final void setSphereMap(Texture tex) {
		setSphereTexture(tex);
	}

	public final void setSphereTexture(Texture tex) {
		if (tex != null) {
			if (tex.isForModel) {
				throw new IllegalArgumentException();
			}

			if (tex.nPointer == 0) {
				throw new RuntimeException("Texture already disposed");
			}
		}

		mTexture = tex;
	}

	public final void setThreshold(int threshold, int high, int low) {
		setToonParams(threshold, high, low);
	}

	public final void setToonParams(int threshold, int high, int low) {
		if (((threshold | high | low) & 0xFFFFFF00) != 0) {
			throw new IllegalArgumentException();
		}
		mThreshold = threshold;
		mHigh = high;
		mLow = low;
	}

	public final void setTransparency(boolean isEnable) {
		isBlendEnable = isEnable;
	}

	private static native void nInitClass();

	static {
		System.loadLibrary("java_micro3d_v3_32");
		nInitClass();
	}
}
