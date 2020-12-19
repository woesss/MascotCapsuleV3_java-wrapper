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

public class Vector3D {
	public int x;
	public int y;
	public int z;

	public Vector3D() {
	}

	public Vector3D(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}

	public Vector3D(Vector3D v) {
		set(v);
	}

	public final int getX() {
		return x;
	}

	public final int getY() {
		return y;
	}

	public final int getZ() {
		return z;
	}

	public final int innerProduct(Vector3D v) {
		if (v == null) {
			throw new NullPointerException();
		}
		return nDot(v);
	}

	public static int innerProduct(Vector3D v1, Vector3D v2) {
		if (v1 == null || v2 == null) {
			throw new NullPointerException();
		}
		return nDot2(v1, v2);
	}

	public final void outerProduct(Vector3D v) {
		if (v == null) {
			throw new NullPointerException();
		}
		nCross(v);
	}
	public static Vector3D outerProduct(Vector3D v1, Vector3D v2) {
		if (v1 == null || v2 == null) {
			throw new NullPointerException();
		}
		Vector3D r = new Vector3D();
		nCross2(v1, v2, r);
		return r;
	}

	public final void set(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	public final void set(Vector3D v) {
		if (v == null) {
			throw new NullPointerException();
		}
		x = v.x;
		y = v.y;
		z = v.z;
	}
	public final void setX(int x) {
		this.x = x;
	}
	public final void setY(int y) {
		this.y = y;
	}

	public final void setZ(int z) {
		this.z = z;
	}

	public native final void unit();

	private native void nCross(Vector3D v);
	private native int nDot(Vector3D v);

	private static native void nCross2(Vector3D v1, Vector3D v2, Vector3D r);
	private static native int nDot2(Vector3D v1, Vector3D v2);
	private static native void nInitClass();

	static {
		System.loadLibrary("java_micro3d_v3_32");
		nInitClass();
	}
}
