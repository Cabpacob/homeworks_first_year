#include "BitWriter.h"

bool BitWriter::write(bool bit, std::ostream &os)
{
    buffer ^= (bit << count);
    count++;

    if(count == 8)
    {
        os.write((char*)&buffer, sizeof(buffer));
        buffer = 0;
        count = 0;
        return 1;
    }
    return 0;
}

bool BitWriter::dump(std::ostream &os)
{
    if(count == 0)
        return 0;

    os.write((char*)&buffer, sizeof(buffer));
    buffer = 0;
    count = 0;
    return 1;
}
