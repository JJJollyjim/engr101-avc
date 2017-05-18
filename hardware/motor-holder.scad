motor_diameter = 12;
motor_flat_height = 10;

grid = 4.98;
grid_hole_diam = 3;

inf = 1e7;
border = 3.5;
depth = 14.7;
drop = 8.5;

base_offset = 2;

$fn=100;

module motor_outline() {
    intersection() {
        circle(d=motor_diameter);
        translate([-motor_flat_height/2, -inf/2]) square([motor_flat_height, inf ]);
    }
}

linear_extrude(height=depth)
difference() {
    union() {
        offset(r=border) motor_outline();
        translate([0, -(motor_diameter/2 + border)]) square([drop, motor_diameter+2*border]);
    }
    motor_outline();
}

module holes() {
    translate([grid*2.5, 0]) circle(d=grid_hole_diam);
    translate([-grid*2.5, 0]) circle(d=grid_hole_diam);
    
    translate([grid*2.5, grid*2]) circle(d=grid_hole_diam);
    translate([-grid*2.5, grid*2]) circle(d=grid_hole_diam);
}

translate([motor_flat_height/2,0,grid_hole_diam/2+base_offset]) rotate([90, 0, 90]) linear_extrude(height=drop-motor_flat_height/2) difference() {
    hull() offset(r=base_offset) holes();
    //translate([-grid*3, -2.5]) square([grid*6, 500]);
    
    holes();
}