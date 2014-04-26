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
 * @brief parport2 parallel-port-raw/src/ParallelPort.cpp
 * @file ParallelPort.cpp
 * @date 03/04/2012
 * @author Wolfgang Hackenberg <wolfih@gmx.de>
 */

#include <sys/io.h>
#include <sstream>

#include "ParallelPort.h"

ParallelPort::ParallelPort() : _open(false) {}

void ParallelPort::open(int baseAddress) throw (std::runtime_error) {
	char byteCount = 3;
	char addressClaim = 1;

	if (ioperm(baseAddress, byteCount, addressClaim) != 0) {
		std::stringstream message;
		message << "Unable to open port " << std::hex << std::showbase
				<< baseAddress << ". Try executing with sudo.";
		throw std::runtime_error(message.str());
	}

	_dataAddress = baseAddress;
	_statusAddress = baseAddress + 1;
	_controlAddress = baseAddress + 2;

	_open = true;
}

bool ParallelPort::isOpen() {
	return _open;
}

void ParallelPort::close() throw (std::runtime_error) {
	_open = false;

	char byteCount = 3;
	char addressRelease = 0;
	// _dataAddress is first byte of port.
	if (ioperm(_dataAddress, byteCount, addressRelease) != 0) {
		std::stringstream message;
		message << "Unable to close port 0x" << std::hex << std::showbase
				<< _dataAddress << ".";
		throw std::runtime_error(message.str());
	}
}

char ParallelPort::readData() {
	return inb(_dataAddress);
}

char ParallelPort::readControl() {
	return inb(_controlAddress);
}

char ParallelPort::readStatus() {
	return inb(_statusAddress);
}

void ParallelPort::writeData(char value) {
	outb(value, _dataAddress);
}

void ParallelPort::writeControl(char value) {
	outb(value, _controlAddress);
}

