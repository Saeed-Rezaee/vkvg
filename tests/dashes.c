#include "test.h"
static float offset = 0;
void test(){
	offset += 0.1f;

	VkvgContext ctx = vkvg_create(surf);
	vkvg_clear(ctx);
	//const float dashes[] = {160.0f, 80};
	float dashes[] = {700.0f, 30};
	//const float dashes[] = {50, 40};
	vkvg_set_line_cap(ctx, VKVG_LINE_CAP_ROUND);
	vkvg_set_dash(ctx, dashes, 2, offset);
	vkvg_set_line_width(ctx, 20);
	vkvg_set_source_rgb(ctx, 0, 0, 1);

	vkvg_move_to (ctx, 150, 50);
	vkvg_rel_line_to (ctx, 500, 0);
	vkvg_rel_line_to (ctx, 0, 200);
	vkvg_rel_line_to (ctx, 200, 0);
	vkvg_rel_line_to (ctx, 0, 500);
	vkvg_rel_line_to (ctx, -700, 0);
	vkvg_close_path(ctx);
	vkvg_stroke (ctx);

	dashes[0] = 0;
	dashes[1] = 30;
	vkvg_set_dash(ctx, dashes, 2, offset);

	vkvg_set_source_rgb(ctx, 0, 1, 0);

	vkvg_move_to (ctx, 200, 100);
	vkvg_rel_line_to (ctx, 400, 0);
	vkvg_rel_line_to (ctx, 0, 200);
	vkvg_rel_line_to (ctx, 200, 0);
	vkvg_rel_line_to (ctx, 0, 400);
	vkvg_rel_line_to (ctx, -600, 0);
	vkvg_close_path(ctx);
	vkvg_stroke (ctx);

	vkvg_destroy(ctx);
}

void test2() {
	VkvgContext ctx = vkvg_create(surf);

	const float dashes[] = { 0, 8 };
	vkvg_set_line_cap(ctx, VKVG_LINE_CAP_ROUND);
	vkvg_set_dash(ctx, dashes, 2, 0);
	vkvg_set_line_width(ctx, 4);

	vkvg_move_to(ctx, 100, 400);
	vkvg_curve_to(ctx, 100, 100, 600, 700, 600, 400);
	vkvg_curve_to(ctx, 1000, 100, 100, 800, 1000, 800);
	vkvg_curve_to(ctx, 1000, 500, 700, 500, 700, 100);
	//vkvg_close_path(ctx);

	//vkvg_set_source_rgba   (ctx, 0.5,0.0,1.0,0.5);
	//vkvg_fill_preserve(ctx);

	vkvg_set_source_rgba(ctx, 1, 0, 0, 1);
	vkvg_stroke(ctx);

	vkvg_destroy(ctx);
}

int main(int argc, char *argv[]) {
	PERFORM_TEST(test, argc, argv);
	PERFORM_TEST(test2, argc, argv);
	return 0;
}
