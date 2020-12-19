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

public class FigureLayout {
	private AffineTrans mAffine;
	private AffineTrans[] mAffineArray;
	private int mAngle;
	private int mCenterX;
	private int mCenterY;
	private int mFar;
	private int mNear;
	private int mParallelH;
	private int mParallelW;
	private int mPerspectiveH;
	private int mPerspectiveW;
	private int mProjectionType;
	private int mScaleX;
	private int mScaleY;

	public FigureLayout() {
		setAffineTrans((AffineTrans) null);
		mScaleX = 512;
		mScaleY = 512;
	}

	public FigureLayout(AffineTrans trans, int sx, int sy, int cx, int cy) {
		setAffineTrans(trans);
		mScaleX = sx;
		mScaleY = sy;
		mCenterX = cx;
		mCenterY = cy;
	}

	public final AffineTrans getAffineTrans() {
		return mAffine;
	}

	public final int getCenterX() {
		return mCenterX;
	}

	public final int getCenterY() {
		return mCenterY;
	}

	public final int getParallelHeight() {
		return mParallelH;
	}

	public final int getParallelWidth() {
		return mParallelW;
	}

	public final int getScaleX() {
		return mScaleX;
	}

	public final int getScaleY() {
		return mScaleY;
	}

	public final void selectAffineTrans(int idx) {
		if (mAffineArray == null || idx < 0 || idx >= mAffineArray.length) {
			throw new IllegalArgumentException();
		}
		mAffine = mAffineArray[idx];
	}

	public final void setAffineTrans(AffineTrans trans) {
		if (trans == null) {
			trans = new AffineTrans();
			trans.setIdentity();
		}

		if (mAffineArray == null) {
			mAffineArray = new AffineTrans[1];
			mAffineArray[0] = trans;
		}

		mAffine = trans;
	}

	public final void setAffineTrans(AffineTrans[] trans) {
		if (trans == null) {
			throw new NullPointerException();
		}
		if (trans.length == 0) {
			throw new IllegalArgumentException("Array is empty");
		}
		for (int i = 0; i < trans.length; ++i) {
			if (trans[i] == null) {
				throw new NullPointerException("Null element at index=" + i);
			}
		}

		mAffineArray = trans;
	}

	public final void setAffineTransArray(AffineTrans[] trans) {
		setAffineTrans(trans);
	}

	public final void setCenter(int cx, int cy) {
		mCenterX = cx;
		mCenterY = cy;
	}

	public final void setParallelSize(int w, int h) {
		if (w < 0 || h < 0) {
			throw new IllegalArgumentException("with=" + w + ", height=" + h);
		}
		mParallelW = w;
		mParallelH = h;
		mProjectionType = 1;
	}

	public final void setPerspective(int zNear, int zFar, int angle) {
		if (zNear >= zFar || zNear < 1 || zNear > 32766 || zFar > 32767 || angle < 1 || angle > 2047) {
			throw new IllegalArgumentException("zNear=" + zNear+ ", zFar=" + zFar+ ", angle=" + angle);
		}
		mNear = zNear;
		mFar = zFar;
		mAngle = angle;
		mProjectionType = 2;
	}

	public final void setPerspective(int zNear, int zFar, int width, int height) {
		if (zNear >= zFar || zNear < 1 || zNear > 32766 || zFar > 32767 || width < 0 || height < 0) {
			throw new IllegalArgumentException("zNear=" + zNear+ ", zFar=" + zFar+ ", with=" + width + ", height=" + height);
		}
		mNear = zNear;
		mFar = zFar;
		mPerspectiveW = width;
		mPerspectiveH = height;
		mProjectionType = 3;
	}

	public final void setScale(int sx, int sy) {
		mScaleX = sx;
		mScaleY = sy;
		mProjectionType = 0;
	}

	private static native void nInitClass();

	static {
		System.loadLibrary("java_micro3d_v3_32");
		nInitClass();
	}
}
