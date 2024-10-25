import cv2
import numpy as np

# Parameters for ShiTomasi corner detection and Lucas-Kanade optical flow
feature_params = dict(maxCorners=100, qualityLevel=0.3, minDistance=7, blockSize=7)
lk_params = dict(winSize=(15, 15), maxLevel=2, criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# Load video or sequence of frames
cap = cv2.VideoCapture('video.mp4')

# Read the first frame
ret, old_frame = cap.read()
old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)

# Detect initial feature points using ShiTomasi (can substitute with Harris or FAST as needed)
p0 = cv2.goodFeaturesToTrack(old_gray, mask=None, **feature_params)

# Create a mask for drawing the tracked points
mask = np.zeros_like(old_frame)

while True:
    # Read the next frame
    ret, frame = cap.read()
    if not ret:
        break

    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Track points using Lucas-Kanade optical flow
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)

    # Select good points based on the status array
    good_new = p1[st == 1]
    good_old = p0[st == 1]

    # Estimate motion model (affine) based on the matched points
    M, inliers = cv2.estimateAffinePartial2D(good_old, good_new, method=cv2.RANSAC)

    # Handle tracking failures: remove points with large errors or outliers
    if M is None or inliers is None:
        print("Tracking failed for some points. Reinitializing points.")
        p0 = cv2.goodFeaturesToTrack(frame_gray, mask=None, **feature_params)
    else:
        # Draw the tracks for visualization
        for i, (new, old) in enumerate(zip(good_new, good_old)):
            a, b = new.ravel()
            c, d = old.ravel()
            mask = cv2.line(mask, (a, b), (c, d), (0, 255, 0), 2)
            frame = cv2.circle(frame, (a, b), 5, (0, 0, 255), -1)

        # Overlay the tracking visualization on the frame
        img = cv2.add(frame, mask)
        cv2.imshow('KLT Tracker', img)

        # Update the previous frame and previous points
        old_gray = frame_gray.copy()
        p0 = good_new.reshape(-1, 1, 2)

    if cv2.waitKey(30) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
