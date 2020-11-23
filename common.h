#ifndef COMMON_H
#define COMMON_H

#define X_RANGE  3000
#define Y_RANGE  3000
#define Z_RANGE  1000

#define VX_MIN 5
#define VY_MIN 5
#define VZ_MIN 5

#define VX_MAX 40
#define VY_MAX 40
#define VZ_MAX 40

#define Z_CONST 200
#define VZ_CONST 0

#define PROXIMITY_SENSOR_RADIUS 1000

#define MAX_SIMULATED_UAS 10

#define MAX_SENSORS 5

#define LOITER_TIME_THRESHOLD 120

#define WARNING_THRESHOLD 0.01
#define RETURN_THRESHOLD 0.25
#define CAPTURE_THRESHOLD 0.50
#define DESTROY_THRESHOLD 0.75

#define SIMULATED_TIME_DURATION 1000

struct ThreeDVector{
  double x;
  double y;
  double z;
};
typedef struct ThreeDVector ThreeDVector;


#endif

