#include "imu.h"

/* setting */
vector_t sensor_get_imu_ABSOULUTE_ORIENTATION_EULER(sensor_t *obj);
vector_t sensor_get_imu_ABSOLUTE_ORIENTAION_QUATERNION(sensor_t *obj);
vector_t sensor_get_imu_ANGULAR_VELOCITY(sensor_t *obj);
vector_t sensor_get_imu_GRAVITY(sensor_t *obj);
vector_t sensor_get_imu_LINEAR_ACCELERATION(sensor_t *obj);
vector_t sensor_get_imu_MAGNETIC_FIELD_STRENGTH(sensor_t *obj);
vector_t sensor_get_imu_TEMPERATURE(sensor_t *obj);


/* setting */
vector_t sensor_set_imu_ABSOULUTE_ORIENTATION_EULER(sensor_t *obj, double &data);
vector_t sensor_set_imu_ABSOLUTE_ORIENTAION_QUATERNION(sensor_t *obj, double &data);
vector_t sensor_set_imu_ANGULAR_VELOCITY(sensor_t *obj, double &data);
vector_t sensor_set_imu_GRAVITY(sensor_t *obj, double &data);
vector_t sensor_set_imu_LINEAR_ACCELERATION(sensor_t *obj, double &data);
vector_t sensor_set_imu_MAGNETIC_FIELD_STRENGTH(sensor_t *obj, double &data);
vector_t sensor_set_imu_TEMPERATURE(sensor_t *obj, double &data);

