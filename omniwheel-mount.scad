grid = 4.98;
ball_rad = 33/2;
axle_rad = 1.9/2;
grid_hole_diam = 3;

$fn = 30;

inf = 1e3;

ball_drop = ball_rad + 6;
extra_drop = axle_rad + 4;

depth = 5*grid;

module support() {
    polygon([
        [0,0],
        [2.3*grid, 0],
        [1.5*grid, 13],
        [1.5*grid, ball_drop+extra_drop],
        [0, ball_drop+extra_drop]
    ]);
}


module axle() {
    translate([-inf/2,ball_drop,0]) rotate([0, 90, 0]) cylinder(h=inf, r=axle_rad);
}



//translate([10*grid/2, ball_drop]) sphere(r=ball_rad);

difference() {

    translate([0,0,-depth/2]) linear_extrude(height=depth) {
        translate([0,-5]) square([10*grid, 5]);
        support();
        translate([10*grid, 0]) mirror() support();
    }
    axle();
    rotate([90,0,0]) translate([grid*3, 3*grid/2, -inf/2]) cylinder(h=inf, d=grid_hole_diam);
    rotate([90,0,0]) translate([grid*3, -3*grid/2, -inf/2]) cylinder(h=inf, d=grid_hole_diam);
    rotate([90,0,0]) translate([grid*7, -3*grid/2, -inf/2]) cylinder(h=inf, d=grid_hole_diam);
    rotate([90,0,0]) translate([grid*7, 3*grid/2, -inf/2]) cylinder(h=inf, d=grid_hole_diam);
}


//axle();