#include <stdio.h>
#include <stdint.h>
#include <vector>

typedef uint8_t byte;

const byte encByte = 0xff;

struct Type
{
    uint8_t room;
    uint16_t roomoffs;
};
typedef std::vector<Type> Types;

const char *dir;

uint8_t readByte(FILE *f)
{
    byte b;
    fread(&b, 1, 1, f);
    return b ^ encByte;
}

uint16_t readUint16LE(FILE *f)
{
    byte b[2];
    fread(b, 2, 1, f);
    return (b[0] ^ encByte) + (b[1] ^ encByte) * 0x100;
}

FILE *openRoom(int i)
{
    char fname[1024];
    sprintf(fname, "%s/%02d.LFL", dir, i);
    return fopen(fname, "rb");
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

    dir = argv[1];

    FILE *f = openRoom(0);

    int _numGlobalObjects = 775;
    int _numRooms = 55;

    // costumes 25-36 are special. see v1MMNEScostTables[] in costume.cpp
    // costumes 37-76 are room graphics resources
    // costume 77 is a character set translation table
    // costume 78 is a preposition list
    // costume 79 is unused but allocated, so the total is a nice even number :)
    int _numCostumes = 80;
    Types costumes(_numCostumes);
    int _numScripts = 200;
    Types scripts(_numScripts);
    int _numSounds = 100;
    
	// readMAXS(0);
	int _numVariables = 800;				// 800
	int _numBitVariables = 4096;			// 2048
	int _numLocalObjects = 200;				// 200
	int _numArray = 50;
	int _numVerbs = 100;
	int _numNewNames = 50;
	void * _objectRoomTable = NULL;
	int _numCharsets = 9;					// 9
	int _numInventory = 80;					// 80
	int _numGlobalScripts = 200;
	int _numFlObject = 50;

	int _shadowPaletteSize = 256;

    int i;

	//byte *_shadowPalette = (byte *) calloc(_shadowPaletteSize, 1);	// FIXME - needs to be removed later
	// allocateArrays();

	printf("Magic %x\n", readUint16LE(f)); /* version magic number */
	for (i = 0; i != _numGlobalObjects; i++) {
	 	byte tmp = readByte(f);
        //printf("global %d owner %d state %d\n", i, tmp & 15, tmp >> 4);

	// 	_objectOwnerTable[i] = tmp & OF_OWNER_MASK;
	// 	_objectStateTable[i] = tmp >> OF_STATE_SHL;
	}

	// for (i = 0; i < _numRooms; i++) {
	// 	_res->_types[rtRoom][i]._roomno = i;
	// }
	fseek(f, _numRooms, SEEK_CUR);
	for (i = 0; i < _numRooms; i++) {
	// 	_res->_types[rtRoom][i]._roomoffs = _fileHandle->readUint16LE();
        uint16_t offs = readUint16LE(f);
        // always 0
        //printf("room %d offset %x\n", i, offs);
	}

	for (i = 0; i < _numCostumes; i++) {
	// 	_res->_types[rtCostume][i]._roomno = _fileHandle->readByte();
        costumes[i].room = readByte(f);
	}
	for (i = 0; i < _numCostumes; i++) {
	// 	_res->_types[rtCostume][i]._roomoffs = _fileHandle->readUint16LE();
        costumes[i].roomoffs = readUint16LE(f);
        printf("costume %d room %d offs %x\n", i, costumes[i].room, costumes[i].roomoffs);
	}

	for (i = 0; i < _numScripts; i++) {
	// 	_res->_types[rtScript][i]._roomno = _fileHandle->readByte();
        scripts[i].room = readByte(f);
	}
	for (i = 0; i < _numScripts; i++) {
	// 	_res->_types[rtScript][i]._roomoffs = _fileHandle->readUint16LE();
        scripts[i].roomoffs = readUint16LE(f);
        printf("script %d room %d offs %x\n", i, scripts[i].room, scripts[i].roomoffs);
	// 	if (_res->_types[rtScript][i]._roomoffs == 0xFFFF)
	// 		_res->_types[rtScript][i]._roomoffs = (uint32)RES_INVALID_OFFSET;
	}

    // TODO

	// for (i = 0; i < _numSounds; i++) {
	// 	_res->_types[rtSound][i]._roomno = _fileHandle->readByte();
	// }
	// for (i = 0; i < _numSounds; i++) {
	// 	_res->_types[rtSound][i]._roomoffs = _fileHandle->readUint16LE();
	// 	if (_res->_types[rtSound][i]._roomoffs == 0xFFFF)
	// 		_res->_types[rtSound][i]._roomoffs = (uint32)RES_INVALID_OFFSET;
	// }

    fclose(f);

    return 0;
}
