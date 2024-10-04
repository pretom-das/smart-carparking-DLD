module Parking_System(
    input [7:0] car,              
    output [6:0] car_count_display,   
    output [6:0] empty_space_display  
);
    wire [3:0] car_count;  
    wire [3:0] empty_spaces;  

    // Sum the car inputs using an adder
    assign car_count = car[0] + car[1] + car[2] + car[3] + car[4] + car[5] + car[6] + car[7];

    // Calculate empty spaces (8 - car_count)
    assign empty_spaces = 4'b1000 - car_count;

    // Instantiate 7-segment display drivers for car count and empty spaces
    SevenSegDriver display1 (.binary_in(car_count), .seg_out(car_count_display));
    SevenSegDriver display2 (.binary_in(empty_spaces), .seg_out(empty_space_display));
endmodule

// 7-segment display driver module (BCD to 7-segment)
module SevenSegDriver(
    input [3:0] binary_in,
    output reg [6:0] seg_out
);
    always @(*) begin
        case (binary_in)
            4'b0000: seg_out = 7'b1000000; // 0
            4'b0001: seg_out = 7'b1111001; // 1
            4'b0010: seg_out = 7'b0100100; // 2
            4'b0011: seg_out = 7'b0110000; // 3
            4'b0100: seg_out = 7'b0011001; // 4
            4'b0101: seg_out = 7'b0010010; // 5
            4'b0110: seg_out = 7'b0000010; // 6
            4'b0111: seg_out = 7'b1111000; // 7
            4'b1000: seg_out = 7'b0000000; // 8
            default: seg_out = 7'b1111111; // Blank/Error
        endcase
    end
endmodule
