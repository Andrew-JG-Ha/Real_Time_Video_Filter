----------------------------------------------------------------------------------
-- Company: N/A
-- Engineer: Shakeeb Arsalan Zacky (Engineering Student)
-- 
-- Create Date: 02/25/2024 08:25:15 PM
-- Design Name: RGB_to_RGBX.vhd
-- Module Name: RGB_to_RGBX - Behavioral
-- Project Name: RGB_to_RGBX
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity RGB_to_RGBX is
    Port ( 
           RGB_in : in STD_LOGIC_VECTOR(11 downto 0);
--           R_in : in STD_LOGIC_VECTOR (3 downto 0);
--           G_in : in STD_LOGIC_VECTOR (3 downto 0);
--           B_in : in STD_LOGIC_VECTOR (3 downto 0);
           clk : in STD_LOGIC;
           
           address_in     : in STD_LOGIC_VECTOR(18 downto 0);
           address_out    : out STD_LOGIC_VECTOR(18 downto 0);
           writeEnable_in : in STD_LOGIC;
           RGBX_out : out STD_LOGIC_VECTOR(15 downto 0);
           writeEnable_out : out STD_LOGIC
           );
end RGB_to_RGBX;

architecture Behavioral of RGB_to_RGBX is
    signal redScaled, greenScaled, blueScaled, res : unsigned(7 downto 0);
    signal redDelay1, greenDelay1, blueDelay1 : std_logic_vector(3 downto 0);
    signal redDelay2, greenDelay2, blueDelay2 : std_logic_vector(3 downto 0);
    signal writeEnableDelay1, writeEnableDelay2 : std_logic;
    signal addressDelay1, addressDelay2 : std_logic_vector(18 downto 0);
    
begin
    PROCESS(clk)
    BEGIN
        redDelay1 <= RGB_in(11 downto 8);
        redDelay2 <= redDelay1;
--        R_out <= redDelay2;
        
        greenDelay1 <= RGB_in(7 downto 4);
        greenDelay2 <= greenDelay1;
--        G_out <= greenDelay2;
        
        blueDelay1 <= RGB_in(3 downto 0);
        blueDelay2 <= blueDelay1;
--        B_out <= blueDelay2;
        
        writeEnableDelay1 <= writeEnable_in;
        writeEnableDelay2 <= writeEnableDelay1;
        writeEnable_out <= writeEnableDelay2;
        
        addressDelay1 <= address_in;
        addressDelay2 <= addressDelay1;
        address_out <= addressDelay2;
    --    redScaled <= "01001100" * unsigned(R_in); -- Binary value 76 multiplied by the R value gives 0.3*R
    --    greenScaled <= "01001100" * unsigned(G_in); -- Binary value 151 multiplied by the G value gives 0.59*G
    --    blueScaled <= "00011100" * unsigned(B_in); -- Binary value 28 multiplied by the B value gives 0.11*B
    
        redScaled <= "0101" * unsigned(RGB_in(11 downto 8)); -- Binary value 5 multiplied by the R value gives 0.3*R
        greenScaled <= "1010" * unsigned(RGB_in(7 downto 4)); -- Binary value 10 multiplied by the G value gives 0.59*G
        blueScaled <= "0010" * unsigned(RGB_in(3 downto 0)); -- Binary value 2 multiplied by the B value gives 0.11*B
    
--        redScaled <= "0101" * unsigned(R_in); -- Binary value 5 multiplied by the R value gives 0.3*R
--        greenScaled <= "1010" * unsigned(G_in); -- Binary value 10 multiplied by the G value gives 0.59*G
--        blueScaled <= "0010" * unsigned(B_in); -- Binary value 2 multiplied by the B value gives 0.11*B
        res <= redScaled + greenScaled + blueScaled;
        RGBX_out <= redDelay2 & greenDelay2 & blueDelay2 & std_logic_vector(res(7 DOWNTO 4));
--        X_out <= std_logic_vector(res(7 DOWNTO 4));
    END PROCESS;
end Behavioral;