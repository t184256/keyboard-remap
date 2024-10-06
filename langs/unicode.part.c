#define emit_unicode(k1, k2, k3, k4) \
	do { \
		emit_press(KEY_LEFTCTRL); \
		emit_press(KEY_LEFTSHIFT); \
		emit_press(KEY_U); emit_release(KEY_U); \
		usleep(5000); \
		emit_release(KEY_LEFTSHIFT); \
		emit_release(KEY_LEFTCTRL); \
		emit_press(KEY_LEFTALT); \
		emit_release(KEY_LEFTALT); \
		usleep(5000); \
		emit_press(KEY_ ## k1); emit_release(KEY_ ## k1); \
		emit_press(KEY_ ## k2); emit_release(KEY_ ## k2); \
		emit_press(KEY_ ## k3); emit_release(KEY_ ## k3); \
		emit_press(KEY_ ## k4); emit_release(KEY_ ## k4); \
		emit_press(KEY_SPACE); emit_release(KEY_SPACE); \
		usleep(20000); \
	} while(0)
