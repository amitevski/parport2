/*
 * Author: Wolfgang Hackenberg <whackenb@gmail.com>
 *
 * API adopted from Matheus Neder's parallel-port:
 * https://code.google.com/p/parallel-port/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief parport2 parallel-port-raw/include/ParallelPort.h
 * @file ParallelPort.h
 * @date 03/04/2012
 * @author Wolfgang Hackenberg <wolfih@gmx.de>
 */
#ifndef PARALLEL_PORT_H_
#define PARALLEL_PORT_H_

#include <stdexcept>

/**
 * ParallelPort class for low level access to the parallel port
 * using inb and outb macros under Linux.
 * Requires root privileges to access parallel port.
 *
 * API adopted from Matheus Neder's parallel-port project
 * to serve as a replacement where low level access is required.
 * Original project's home:
 * https://code.google.com/p/parallel-port/
 *
 * @author Wolfgang Hackenberg <wolfih@gmx.de>
 */
class ParallelPort {

private:
	int _dataAddress;
	int _statusAddress;
	int _controlAddress;
	bool _open;

public:
	ParallelPort();

	/**
	 * Claims access for base address and the following two bytes.
	 *
	 * @param open Address of the parallel port.
	 * Typical addresses are 0x378 for first built-in port or
	 * 0x2000 parallel port  miniPCIe extension card.
	 */
	void open(int baseAddress) throw (std::runtime_error);

	/**
	 * Checks if port is open.
	 */
	bool isOpen();

	/**
	 * Releases the three bytes claimed by open.
	 */
	void close() throw (std::runtime_error);

	/**
	 * Reads data byte.
	 */
	char readData();

	/**
	 * Reads previous written control byte.
	 */
	char readControl();

	/**
	 * Reads status byte.
	 */
	char readStatus();

	/**
	 * Writes data byte.
	 */
	void writeData(char value);

	/**
	 * Writes control byte.
	 */
	void writeControl(char value);
};

#endif /* PARALLEL_PORT_H_ */
