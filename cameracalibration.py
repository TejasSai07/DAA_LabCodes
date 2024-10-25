import cv2
import numpy as np
import glob

# Defining the dimensions of checkerboard
CHECKERBOARD = (12, 12)
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 50, 0.0001)

# Creating vectors to store 3D and 2D points for each checkerboard image
objpoints = []  # 3D points in real world space
imgpoints = []  # 2D points in image plane

# Defining the world coordinates for 3D points
objp = np.zeros((CHECKERBOARD[0] * CHECKERBOARD[1], 3), np.float32)
objp[:, :2] = np.mgrid[0:CHECKERBOARD[0], 0:CHECKERBOARD[1]].T.reshape(-1, 2)

# Extracting paths of individual images stored in a given directory
images = glob.glob('./calib_example/*.tif')

for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Find the chessboard corners
    ret, corners = cv2.findChessboardCorners(
        gray, CHECKERBOARD,
        cv2.CALIB_CB_ADAPTIVE_THRESH + cv2.CALIB_CB_FAST_CHECK + cv2.CALIB_CB_NORMALIZE_IMAGE
    )

    # If found, refine pixel coordinates and add points to objpoints and imgpoints
    if ret:
        objpoints.append(objp)
        corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
        imgpoints.append(corners2)

        # Draw and display the corners
        img = cv2.drawChessboardCorners(img, CHECKERBOARD, corners2, ret)
        cv2.imshow('img', img)
        cv2.waitKey(500)

cv2.destroyAllWindows()

# Perform camera calibration
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

# Display the intrinsic parameters (Camera matrix) and extrinsic parameters (rvecs and tvecs)
print("Intrinsic parameters (Camera matrix):\n", mtx)
print("\nDistortion coefficients:\n", dist)
print("\nExtrinsic parameters:")
for i in range(len(rvecs)):
    print(f"\nRotation vector for image {i}:\n", rvecs[i])
    print(f"Translation vector for image {i}:\n", tvecs[i])

# Verify the calibration results by reprojecting the points
for i, fname in enumerate(images):
    img = cv2.imread(fname)
    imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)

    # Draw reprojected points and display them
    for j in range(len(imgpoints2)):
        img = cv2.circle(img, tuple(imgpoints2[j].ravel().astype(int)), 5, (0, 0, 255), -1)
    
    cv2.imshow('Reprojected Points', img)
    cv2.waitKey(500)

cv2.destroyAllWindows()
