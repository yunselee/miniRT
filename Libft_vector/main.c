#include "vector3.h"
#include "quaternion.h"
#include "matrix33.h"
#include "transform.h"
#include <stdio.h>

void show_vec3(t_vec3 v);
void show_quat(t_quat v);
void show_mat33(t_mat33 v);

int main()
{
	t_vec3	v1 = create_vec3(1, 1, 1);
	show_vec3(v1);
	t_vec3 v2 = vec3_scale(&v1, 2);
	show_vec3(v2);

	t_quat	q1 = quat_by_elements(1,1,1,1);
	t_quat	q2 = quat_by_vector(0.4, &v2);
	show_quat(q1);
	show_quat(q2);

	t_vec3 v3 = create_vec3(0,0,0.4);
	t_mat33	m1 = create_mat33(&v1, &v2, &v3);
	show_mat33(m1);
	t_mat33 T = mat33_trans(&m1);
	show_mat33(T);
	m1 = mul_mat33(&m1, &T);
	show_mat33(m1);

	t_vec3	axis = create_vec3(0, 0, 1);
	show_vec3(axis);
	t_vec3	P = create_vec3(1,0,0);
	show_vec3(P);
	t_vec3	Q = rotate_vec3_deg(&axis, 45, &P);
	show_vec3(Q);
}

#include <stdio.h>
void show_vec3(t_vec3 v)
{
	printf("vec:<%3.3f,%3.3f,%3.3f>\n", v.x, v.y, v.z);
}
void show_quat(t_quat q)
{
	printf("quat:<%3.3f|%3.3f,%3.3f,%3.3f>\n", q.w, q.k.x, q.k.y, q.k.z);
}
void show_mat33(t_mat33 m)
{
	printf("mat33\n");
	printf("⎡%3.3f %3.3f %3.3f⎤\n", m.r1.x, m.r2.x, m.r3.x);
	printf("⎢%3.3f %3.3f %3.3f⎥\n", m.r1.y, m.r2.y, m.r3.y);
	printf("⎣%3.3f %3.3f %3.3f⎦\n", m.r1.z, m.r2.z, m.r3.z);
}

/*
vec:<1.000,1.000,1.000>
vec:<2.000,2.000,2.000>
quat:<1.000|1.000,1.000,1.000>
quat:<0.400|2.000,2.000,2.000>
mat33
⎡1.000 2.000 0.000⎤
⎢1.000 2.000 0.000⎥
⎣1.000 2.000 0.400⎦
mat33
⎡1.000 1.000 1.000⎤
⎢2.000 2.000 2.000⎥
⎣0.000 0.000 0.400⎦
mat33
⎡5.000 5.000 5.000⎤
⎢5.000 5.000 5.000⎥
⎣5.000 5.000 5.160⎦
*/