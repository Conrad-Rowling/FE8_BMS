/******************************************************************************
*
* Copyright (c) 2012-2014 Linear Technology Corporation (LTC)
* All Rights Reserved
*
*******************************************************************************
*
* Subject to Customer’s acceptance of the following terms and conditions, both
* redistribution of this software by Customer in binary form only and internal
* use of this software by Customer in source form, with or without modification,
* are permitted:
*
* - LTC has granted use rights to Customer in writing.
*
* - Any redistributions by Customer in binary form must include the above
*   copyright notice, this list of conditions and the following disclaimer in
*   the documentation and/or other materials provided with the redistribution.
*
* - Permission for internal use of the Software in source form is strictly
*   limited to Customer only and its controlled subsidiaries. Contractors,
*   consultants and all other third parties must seek and obtain separate
*   written use rights from LTC.
*
* - Other than for the above copyright notice and the below disclaimer, neither
*   the name of Linear Technology, Inc., Linear Technology Corporation (LTC)
*   nor the names of any of their contributors may be used by Customer for any
*   purpose, including, without limitation, the endorsement or promotion of any
*   products derived from this software without the fully informed, specific,
*   prior written permission from LTC.
*
*******************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY LTC "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL LTC OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/*! @file
    @ingroup LTPSM_InFlightUpdate
    Library Header File for NVM
*/


#ifndef NVM_H_
#define NVM_H_

#include <stdbool.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../LT_SDReader/LT_SDReader.h"
#include "../LT_PMBUS/LT_PMBus.h"
#include "../LT_PMBUS/LT_SMBusNoPec.h"
#include "../LT_PMBUS/LT_SMBusPec.h"
#include "../LT_PMBUS/LT_I2CBus.h"
#include "main_record_processor.h"
#include "hex_file_parser.h"


extern LT_PMBus * pmbus__;				//!< global accessor for IFU helper files
extern LT_SMBusNoPec * smbusNoPec__;	//!< global accessor for IFU helper files
extern LT_SMBusPec * smbusPec__;		//!< global accessor for IFU helper files


	// extern uint8_t get_hex_data(void);
	
	//! Data retrieving method.
	extern uint8_t get_hex_data(void);
	//! Data retrieving method.
	extern uint8_t get_record_data(void);
	//! Data retrieving method.
	extern pRecordHeaderLengthAndType get_record(void);
	
class NVM
{
private:
	uint8_t* addr;
	uint8_t numAddrs;
	
public:
	//! Constructor.
	NVM(LT_PMBus*,		//!< reference to pmbus object for this library to use
		LT_SMBusNoPec*, //!< reference to no pec smbus object
		LT_SMBusPec*, 	//!< reference to pec smbus object
		uint8_t*, 		//!< i2c addresses on the board to program.
		uint8_t			//!< number of addresses
		);
	
	//! Destructor
	~NVM();
	
	// bool load_hex_file(int);
	
	//! Loads file from SD card.  (Abstract this out if you have time.  See README)
	//! @return true if file found.
	bool load_hex_file(char*	//!< name of file to load.
						);
	
	//! programs board with the loaded hex file.
	//! @return true if successful.
	bool program();
	
	//! verifies board NVM with the loaded hex file.
	//! @return true if NVM configuration matches the loaded ICP file.
	bool verify();
};

/*static prog_uchar icp1[] PROGMEM  = {":2000000006001800000008001B0001000000060018001000090010005B001000C008001B09\
:20002000000000303A08000F005B000338060018000100090010005B00108049060018001F\
:200040001100090010003000100092090001003000000100090004003000000000C800095B\
:20006000003000BF0000FBE8CA40CA00CB00CA00C200000000000000C93010801E0B33415D\
:20008000850BC20A0AA4828FE28C418A7F418A000000007FB328B8B266EA08B8E3C0CD80FE\
:2000A000B8B80A6A2C0A310260EB20EBC0B8E2EDD280F2589F2F0000000000001700004293\
:2000C000C08012EE2403E893330F3C4000800040801E08004185127B10B8828FE26D4171ED\
:2000E0007F418900790000007FB350B8B266EA08B8E3C0CD80B8B8105E1004FB4AEB20EB25\
:20010000C0B8F3A86DD280F258D9AD00000000000017000042C08012EE03E893330F3C4068\
:2001200000800041210900010030001001000900040030001001000A000A003000EF0040D1\
:2001400040090001003000BD01000A000A003000EF004040090004003000BD0000090001B0\
:20016000003000BD012B0A000A003000EF004040090001003000BD01D40A000A003000EFB4\
:20018000004040090004003000BD00D4090001003000BD01000A000A003000EF004040095D\
:2001A0000004003000BD0000090001003000BD012B0A000A003000EF00404009000100303E\
:2001C00000BD01D40A000A003000EF004040090004003000BD00D4090001003000BE002BE9\
:2001E0000A000A003000EF004040090004003000BD0000090001003000BD002B0A000A001C\
:200200003000EF004040090001003000BD00D40A000A003000EF004040090004003000BDC7\
:2002200000D40A0005003000BF0000040A000A003000EF0040400A0005003000BF006000D7\
:200240000A000A003000EF004040090001003000BD00000A000A003000EF00404009000434\
:20026000003000BD0000090001003000BD002B0A000A003000EF004040090001003000BDC5\
:2002800000D40A000A003000EF004040090004003000BD00D408001E003000BF00090004E7\
:2002A000003000BD000009000C00300000E80306000D000A000600180002000600180012B4\
:2002C00000060018001300090001003000000100090004003000000000090001003000102B\
:2002E00001000900040030001001000A000A003000EF004040090001003000BD01000A00FA\
:200300000A003000EF004040090004003000BD0000090001003000BD012B0A000A003000D3\
:20032000EF004040090001003000BD01D40A000A003000EF004040090004003000BD00D401\
:20034000090001003000BD01000A000A003000EF004040090004003000BD000009000100EE\
:200360003000BD012B0A000A003000EF004040090001003000BD01D40A000A003000EF00B2\
:200380004040090004003000BD00D40A0005003000BF0000040A000A003000EF0040400A50\
:2003A0000005003000BF0060000A000A003000EF00404008001F003000BF000900040030E3\
:2003C00000BD000009001000300010801B060018001100090010003200100039090001009F\
:2003E0003200000100090004003200000000080209003200BF00801E009A31008015341F36\
:200400002F40CA00CA48EA0B397F9036A42C292A7F9AB3BF663FB266B47808EAB8C0E3003A\
:200420008080CDB800CBB8C0CA00CA80C3B8212E232D8FFA807CD2C0D3B88FFA000000009B\
:200440000000000000000000008000808000FB0F000000000FAA0F0000EE12008045022063\
:20046000EB008000800F300000C23C0F0700400080801E9A395E00807B3CB93674EA3E42AB\
:200480007F5D3FD733F6307F9AB3BF66B266B47808EAB8C0E3CA008080CDB892356B3431A9\
:2004A000FA80D2C0D3B8EDFA00000000000000800080800000E100A0010000C23C0F00406F\
:2004C0000080801E004000803343CD3C66EA9A497F66469A394066367F9AB3BF66B266B4F5\
:2004E0007808EAB8C0E3008080CDB8853B3D3AA8F380D2C0D3EFB84AFBF3CB000000000051\
:2005000080008080000000CB010000C23C0F00400080801E66AF460080EB49E142A2EAF571\
:20052000507F704D5C3FD73B7F9AB3BF66B266B47808EAB8C05DE3008080CDB87841104015\
:20054000EDF280D2C0D3B8A8FB4B7F000000000080008080003B0000D7010000C23C0F0012\
:200560004000800000000000000000000000000000000000004B0000000000000000000070\
:2005800000000000000000000000000000000000000000000000000000000000000000005B\
:2005A00000000000000000000000000000000000000000000000000000000000000000003B\
:2005C00000000000000000000000000000000000000000000000000000000000000000001B\
:2005E0000000000000000000000000000000000000000000000009000100320010010009A5\
:2006000000040032001001000A000A003200EF004040090001003200BD01000A000A00329E\
:2006200000EF004040090004003200BD0000090001003200BD012B0A000A003200EF0040B5\
:2006400040090001003200BD01D40A000A003200EF004040090004003200BD00D4090001FD\
:20066000003200BD01000A000A003200EF004040090004003200BD0000090001003200BDE0\
:20068000012B0A000A003200EF004040090001003200BD01D40A000A003200EF00404009ED\
:2006A0000004003200BD00D4090001003200BE002B0A000A003200EF00404009000400325A\
:2006C00000BD0000090001003200BD002B0A000A003200EF004040090001003200BD00D4B7\
:2006E0000A000A003200EF004040090004003200BD00D40A0005003200BF0003740A000AEA\
:20070000003200EF0040400A0005003200BF0000010A000A003200EF004040090001003246\
:2007200000BD00000A000A003200EF004040090004003200BD0000090001003200BD002B27\
:200740000A000A003200EF004040090001003200BD00D40A000A003200EF00404009000455\
:20076000003200BD00D408001E003200BF00090004003200BD000009000C00320000E80371\
:2007800006000D000A0006001800120006001800130009000100320000010009000400325F\
:2007A000000000000900010032001001000900040032001001000A000A003200EF004040E7\
:2007C000090001003200BD01000A000A003200EF004040090004003200BD00000900010064\
:2007E0003200BD012B0A000A003200EF004040090001003200BD01D40A000A003200EF0026\
:200800004040090004003200BD00D4090001003200BD01000A000A003200EF0040400900D0\
:2008200004003200BD0000090001003200BD012B0A000A003200EF004040090001003200AF\
:20084000BD01D40A000A003200EF004040090004003200BD00D40A0005003200BF0003740A\
:200860000A000A003200EF0040400A0005003200BF0000010A000A003200EF004040080005\
:200880001F003200BF00090004003200BD00000900100032001080B0060018001100090089\
:2008A000100033001000EF090001003300000100090004003300000000080209003300BF73\
:2008C00000801E00CD1C00803E1E5C1B40CA00CA1F217FAE1FEC197B187F08EAB8C0E3007A\
:2008E0002D8080CDB800CBB8C0CA00CA80C3B8C91A351A310280D2C0D3B8EDEA000000009B\
:20090000DB00000000000000008000FB00000000000F0F0F0F0000EE120080BF0120EB00FA\
:2009200014800080FF300000C207801E002000809A21661ECD247F3323CD1C331B7FC31DD2\
:20094000451F1D030280D2C0D3B831F200000000000080000000B6010000C2801E33230064\
:200960007280F62470217B287FB826AE1FEB1D7FBC200820A8FB80D2C0D3B8EDF200000063\
:200980005000000080000000BD010000C2801E6626008052287A24282C7F3D2A8F22A42096\
:2009A000617FB623F122EDFA80D2C0D3B831FA00000000000080000000B1010000C2801E2A\
:2009C000C1005000800054004C005C7F0058004800447F664ACD4831F280D2C0D3B803021E\
:2009E000430000000000008000000074010000C2801E66560080B85A14525C637F0A5FC242\
:200A0000FA4D70497F5A509F4EEDEA80D2C0D3B83102000000000000800000008F01000009\
:200A20006EC2801E00600080CD64335B666E7F9A6966569A517F48595C57EDE280D2C0D3C5\
:200A4000B5B86002F31E0000000080000000B2010000C2801E9A690080E26E526471797F31\
:200A60009829740B5FC3597F36621960008080D2C0D3B88F02CEB800000000800000007700\
:200A8000A6010000C2000000000000000000000000000000000000000000000000000000ED\
:200AA000C00000000000000000000000000000000000000000000000000000000000000076\
:200AC000000900010033001001000900040033001001000A000A003300EF004040090001B7\
:200AE000003300BD01000A000A003300EF004040090004003300BD0000090001003300BD58\
:200B0000012B0A000A003300EF004040090001003300BD01D40A000A003300EF0040400965\
:200B20000004003300BD00D4090001003300BD01000A000A003300EF0040400900040033FC\
:200B400000BD0000090001003300BD012B0A000A003300EF004040090001003300BD01D42D\
:200B60000A000A003300EF004040090004003300BD00D4090001003300BE002B0A000A00B4\
:200B80003300EF004040090004003300BD0000090001003300BD002B0A000A003300EF005B\
:200BA0004040090001003300BD00D40A000A003300EF004040090004003300BD00D40A0056\
:200BC00005003300BF0001770A000A003300EF0040400A0005003300BF0000010A000A00DA\
:200BE0003300EF004040090001003300BD00000A000A003300EF004040090004003300BDA6\
:200C00000000090001003300BD002B0A000A003300EF004040090001003300BD00D40A0021\
:200C20000A003300EF004040090004003300BD00D408001E003300BF00090004003300BD22\
:200C4000000009000C00330000E80306000D000A00060018001200060018001300090001D9\
:200C6000003300000100090004003300000000090001003300100100090004003300100161\
:200C8000000A000A003300EF004040090001003300BD01000A000A003300EF0040400900E4\
:200CA00004003300BD0000090001003300BD012B0A000A003300EF00404009000100330027\
:200CC000BD01D40A000A003300EF004040090004003300BD00D4090001003300BD01000AF6\
:200CE000000A003300EF004040090004003300BD0000090001003300BD012B0A000A0033DE\
:200D000000EF004040090001003300BD01D40A000A003300EF004040090004003300BD00E2\
:200D2000D40A0005003300BF0001770A000A003300EF0040400A0005003300BF0000010AA4\
:200D4000000A003300EF00404008001F003300BF00090004003300BD000009001000330085\
:200D6000108066090010005B001000C00600180004000900100030001000920A00200030D2\
:200D800000D101800008000F003000EC7F09000C0030000070170900100032001000390CE3\
:200DA0000021003200D1018000000008000F003200EC2B09000C0032000070170900100047\
:200DC00033001000EF0C0021003300D1018000000008000F003300EC0109000C00330000B0\
:080DE000701706001800030063\
:00000001FF\
"};*/

/*static prog_uchar icp2[] PROGMEM  = {":2000000006001800000008001B0001000000060018001000090010005B001000C008001B09\
:20002000000000303A08000F005B000338060018000100090010005B00108049060018001F\
:200040001100090010003000100092090001003000000100090004003000000000C800095B\
:20006000003000BF0000FBE8CA40CA00CB00CA00C200000000000000C93010801E0CCD41C2\
:20008000850D710C8029828FE28C4AE97F4AE9000000007FB328B8B266EA08B8E3C0CD8080\
:2000A000B8B80BE8AA0BA60260EB20EBC0B8E2EDD280F258FCB6000000000000170000423C\
:2000C000C08012EEC503E893330F3C4000800040801E08004185127B10B8828FE26D41714C\
:2000E0007F418900790000007FB350B8B266EA08B8E3C0CD80B8B8105E1004FB4AEB20EB25\
:20010000C0B8F3A86DD280F258889000000000000017000042C08012EE03E893330F3C40D6\
:2001200000800041350900010030001001000900040030001001000A000A003000EF0040BD\
:2001400040090001003000BD01000A000A003000EF004040090004003000BD0000090001B0\
:20016000003000BD012B0A000A003000EF004040090001003000BD01D40A000A003000EFB4\
:20018000004040090004003000BD00D4090001003000BD01000A000A003000EF004040095D\
:2001A0000004003000BD0000090001003000BD012B0A000A003000EF00404009000100303E\
:2001C00000BD01D40A000A003000EF004040090004003000BD00D4090001003000BE002BE9\
:2001E0000A000A003000EF004040090004003000BD0000090001003000BD002B0A000A001C\
:200200003000EF004040090001003000BD00D40A000A003000EF004040090004003000BDC7\
:2002200000D40A0005003000BF0000040A000A003000EF0040400A0005003000BF006000D7\
:200240000A000A003000EF004040090001003000BD00000A000A003000EF00404009000434\
:20026000003000BD0000090001003000BD002B0A000A003000EF004040090001003000BDC5\
:2002800000D40A000A003000EF004040090004003000BD00D408001E003000BF00090004E7\
:2002A000003000BD000009000C00300000E80306000D000A000600180002000600180012B4\
:2002C00000060018001300090001003000000100090004003000000000090001003000102B\
:2002E00001000900040030001001000A000A003000EF004040090001003000BD01000A00FA\
:200300000A003000EF004040090004003000BD0000090001003000BD012B0A000A003000D3\
:20032000EF004040090001003000BD01D40A000A003000EF004040090004003000BD00D401\
:20034000090001003000BD01000A000A003000EF004040090004003000BD000009000100EE\
:200360003000BD012B0A000A003000EF004040090001003000BD01D40A000A003000EF00B2\
:200380004040090004003000BD00D40A0005003000BF0000040A000A003000EF0040400A50\
:2003A0000005003000BF0060000A000A003000EF00404008001F003000BF000900040030E3\
:2003C00000BD000009001000300010801B060018001100090010003200100039090001009F\
:2003E0003200000100090004003200000000080209003200BF00801E009A31008015341F36\
:200400002F40CA00CA48EA0B397F9036A42C292A7F9AB3BF663FB266B47808EAB8C0E3003A\
:200420008080CDB800CBB8C0CA00CA80C3B8212E232D8FFA807CD2C0D3B88FFA000000009B\
:200440000000000000000000008000808000FB0F000000000FAA0F0000EE12008044022064\
:20046000EB008000800F300000C23C0F0700400080801E9A397800807B3CB93674EA3E4291\
:200480007F5D3FD733F6307F9AB3BF66B266B47808EAB8C0E3CA008080CDB892356B3431A9\
:2004A000FA80D2C0D3B8EDFA00000000000000800080800000E100A0010000C23C0F00406F\
:2004C0000080801E004000803343CD3C66EA9A497F66469A394066367F9AB3BF66B266B4F5\
:2004E0007808EAB8C0E3008080CDB8853B3D3AA8F380D2C0D3EFB84AFBF3CB000000000051\
:2005000080008080000000CB010000C23C0F00400080801E66AF460080EB49E142A2EAF571\
:20052000507F704D5C3FD73B7F9AB3BF66B266B47808EAB8C05DE3008080CDB87841104015\
:20054000EDF280D2C0D3B8A8FB4B7F000000000080008080003B0000D7010000C23C0F0012\
:200560004000800000000000000000000000000000000000004B0000000000000000000070\
:2005800000000000000000000000000000000000000000000000000000000000000000005B\
:2005A00000000000000000000000000000000000000000000000000000000000000000003B\
:2005C00000000000000000000000000000000000000000000000000000000000000000001B\
:2005E0000000000000000000000000000000000000000000000009000100320010010009A5\
:2006000000040032001001000A000A003200EF004040090001003200BD01000A000A00329E\
:2006200000EF004040090004003200BD0000090001003200BD012B0A000A003200EF0040B5\
:2006400040090001003200BD01D40A000A003200EF004040090004003200BD00D4090001FD\
:20066000003200BD01000A000A003200EF004040090004003200BD0000090001003200BDE0\
:20068000012B0A000A003200EF004040090001003200BD01D40A000A003200EF00404009ED\
:2006A0000004003200BD00D4090001003200BE002B0A000A003200EF00404009000400325A\
:2006C00000BD0000090001003200BD002B0A000A003200EF004040090001003200BD00D4B7\
:2006E0000A000A003200EF004040090004003200BD00D40A0005003200BF0003740A000AEA\
:20070000003200EF0040400A0005003200BF0000010A000A003200EF004040090001003246\
:2007200000BD00000A000A003200EF004040090004003200BD0000090001003200BD002B27\
:200740000A000A003200EF004040090001003200BD00D40A000A003200EF00404009000455\
:20076000003200BD00D408001E003200BF00090004003200BD000009000C00320000E80371\
:2007800006000D000A0006001800120006001800130009000100320000010009000400325F\
:2007A000000000000900010032001001000900040032001001000A000A003200EF004040E7\
:2007C000090001003200BD01000A000A003200EF004040090004003200BD00000900010064\
:2007E0003200BD012B0A000A003200EF004040090001003200BD01D40A000A003200EF0026\
:200800004040090004003200BD00D4090001003200BD01000A000A003200EF0040400900D0\
:2008200004003200BD0000090001003200BD012B0A000A003200EF004040090001003200AF\
:20084000BD01D40A000A003200EF004040090004003200BD00D40A0005003200BF0003740A\
:200860000A000A003200EF0040400A0005003200BF0000010A000A003200EF004040080005\
:200880001F003200BF00090004003200BD00000900100032001080B0060018001100090089\
:2008A000100033001000EF090001003300000100090004003300000000080209003300BF73\
:2008C00000801E00CD1C00803E1E5C1B40CA00CA1F217FAE1FEC197B187F08EAB8C0E3007A\
:2008E0002D8080CDB800CBB8C0CA00CA80C3B8C91A351A310280D2C0D3B8EDEA000000009B\
:20090000DB00000000000000008000FB00000000000F0F0F0F0000EE120080C00120EB00F9\
:20092000BA800080FF300000C207801E002000809A21661ECD247F3323CD1C331B7FC31D2C\
:20094000451F1D030280D2C0D3B831F200000000000080000000B6010000C2801E33230064\
:200960007280F62470217B287FB826AE1FEB1D7FBC200820A8FB80D2C0D3B8EDF200000063\
:200980005000000080000000BE010000C2801E6626008052287A24282C7F3D2A8F22A42095\
:2009A0000B7FB623F122EDFA80D2C0D3B831FA00000000000080000000B2010000C2801E7F\
:2009C000A7005000800054004C005C7F0058004800447F664ACD4831F280D2C0D3B8030238\
:2009E000430000000000008000000074010000C2801E66560080B85A14525C637F0A5FC242\
:200A0000FA4D70497F5A509F4EEDEA80D2C0D3B83102000000000000800000009001000008\
:200A2000DBC2801E00600080CD64335B666E7F9A6966569A517F48595C57EDE280D2C0D358\
:200A4000B5B86002F31E0000000080000000B2010000C2801E9A690080E26E526471797F31\
:200A60009829740B5FC3597F36621960008080D2C0D3B88F02CEB800000000800000007700\
:200A8000A6010000C2000000000000000000000000000000000000000000000000000000ED\
:200AA000C00000000000000000000000000000000000000000000000000000000000000076\
:200AC000000900010033001001000900040033001001000A000A003300EF004040090001B7\
:200AE000003300BD01000A000A003300EF004040090004003300BD0000090001003300BD58\
:200B0000012B0A000A003300EF004040090001003300BD01D40A000A003300EF0040400965\
:200B20000004003300BD00D4090001003300BD01000A000A003300EF0040400900040033FC\
:200B400000BD0000090001003300BD012B0A000A003300EF004040090001003300BD01D42D\
:200B60000A000A003300EF004040090004003300BD00D4090001003300BE002B0A000A00B4\
:200B80003300EF004040090004003300BD0000090001003300BD002B0A000A003300EF005B\
:200BA0004040090001003300BD00D40A000A003300EF004040090004003300BD00D40A0056\
:200BC00005003300BF0001770A000A003300EF0040400A0005003300BF0000010A000A00DA\
:200BE0003300EF004040090001003300BD00000A000A003300EF004040090004003300BDA6\
:200C00000000090001003300BD002B0A000A003300EF004040090001003300BD00D40A0021\
:200C20000A003300EF004040090004003300BD00D408001E003300BF00090004003300BD22\
:200C4000000009000C00330000E80306000D000A00060018001200060018001300090001D9\
:200C6000003300000100090004003300000000090001003300100100090004003300100161\
:200C8000000A000A003300EF004040090001003300BD01000A000A003300EF0040400900E4\
:200CA00004003300BD0000090001003300BD012B0A000A003300EF00404009000100330027\
:200CC000BD01D40A000A003300EF004040090004003300BD00D4090001003300BD01000AF6\
:200CE000000A003300EF004040090004003300BD0000090001003300BD012B0A000A0033DE\
:200D000000EF004040090001003300BD01D40A000A003300EF004040090004003300BD00E2\
:200D2000D40A0005003300BF0001770A000A003300EF0040400A0005003300BF0000010AA4\
:200D4000000A003300EF00404008001F003300BF00090004003300BD000009001000330085\
:200D6000108066090010005B001000C00600180004000900100030001000920A00200030D2\
:200D800000D101800008000F003000EC7F09000C0030000070170900100032001000390CE3\
:200DA0000021003200D1018000000008000F003200EC2B09000C0032000070170900100047\
:200DC00033001000EF0C0021003300D1018000000008000F003300EC0109000C00330000B0\
:080DE000701706001800030063\
:00000001FF\
"};*/

#endif /* NVM_H_ */
