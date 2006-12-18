/* p_vmlinx.h --

   This file is part of the UPX executable compressor.

   Copyright (C) 1996-2006 Markus Franz Xaver Johannes Oberhumer
   Copyright (C) 1996-2006 Laszlo Molnar
   All Rights Reserved.

   UPX and the UCL library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Markus F.X.J. Oberhumer   Laszlo Molnar
   markus@oberhumer.com      ml1050@users.sourceforge.net
 */


#ifndef __UPX_P_VMLINX_H
#define __UPX_P_VMLINX_H

#include "p_elf.h"


/*************************************************************************
// vmlinx/i386 (bare binary Linux kernel image)
**************************************************************************/

template <class TElfClass>
class PackVmlinuxBase : public Packer
{
    typedef Packer super;
protected:
    typedef typename TElfClass::Ehdr Ehdr;
    typedef typename TElfClass::Shdr Shdr;
    typedef typename TElfClass::Phdr Phdr;

public:
    PackVmlinuxBase(InputFile *f) :
        super(f), n_ptload(0), phdri(NULL), shdri(NULL), shstrtab(NULL)
    {
        bele = N_BELE_CTP::getRTP<typename TElfClass::BeLePolicy>();
    }

protected:
    int n_ptload;
    unsigned sz_ptload;
    Phdr *phdri; // from input file
    Shdr *shdri; // from input file
    char *shstrtab; // from input file
    Shdr *p_text;
    Shdr *p_note0;
    Shdr *p_note1;
    Ehdr ehdri; // from input file
};


class PackVmlinuxI386 : public PackVmlinuxBase<ElfClass_LE32>
{
    typedef PackVmlinuxBase<ElfClass_LE32> super;
public:
    PackVmlinuxI386(InputFile *f) : super(f) { }
    virtual ~PackVmlinuxI386();
    virtual int getVersion() const { return 13; }
    virtual int getFormat() const { return UPX_F_VMLINUX_i386; }
    virtual const char *getName() const { return "vmlinux/386"; }
    virtual const char *getFullName(const options_t *) const { return "i386-linux.kernel.vmlinux"; }
    virtual const int *getCompressionMethods(int method, int level) const;
    virtual const int *getFilters() const;
    virtual int getStrategy(Filter &);

    virtual void pack(OutputFile *fo);
    virtual void unpack(OutputFile *fo);

    virtual bool canPack();
    virtual int canUnpack();

protected:
    virtual Elf_LE32_Shdr const *getElfSections();
    virtual void buildLoader(const Filter *ft);
    virtual Linker* newLinker() const;
};


class PackVmlinuxARM : public PackVmlinuxBase<ElfClass_LE32>
{
    typedef PackVmlinuxBase<ElfClass_LE32> super;
public:
    PackVmlinuxARM(InputFile *f) : super(f) { }
    virtual ~PackVmlinuxARM();
    virtual int getVersion() const { return 13; }
    virtual int getFormat() const { return UPX_F_VMLINUX_ARM; }
    virtual const char *getName() const { return "vmlinux/ARM"; }
    virtual const char *getFullName(const options_t *) const { return "ARM-linux.kernel.vmlinux"; }
    virtual const int *getCompressionMethods(int method, int level) const;
    virtual const int *getFilters() const;
    virtual int getStrategy(Filter &);

    virtual void pack(OutputFile *fo);
    virtual void unpack(OutputFile *fo);

    virtual bool canPack();
    virtual int canUnpack();

protected:
    virtual Elf_LE32_Shdr const *getElfSections();
    virtual void buildLoader(const Filter *ft);
    virtual Linker* newLinker() const;
};


class PackVmlinuxAMD64 : public PackVmlinuxBase<ElfClass_LE64>
{
    typedef PackVmlinuxBase<ElfClass_LE64> super;
public:
    PackVmlinuxAMD64(InputFile *f) : super(f) { }
    virtual ~PackVmlinuxAMD64();
    virtual int getVersion() const { return 13; }
    virtual int getFormat() const { return UPX_F_VMLINUX_AMD64; }
    virtual const char *getName() const { return "vmlinux/AMD64"; }
    virtual const char *getFullName(const options_t *) const { return "amd64-linux.kernel.vmlinux"; }
    virtual const int *getCompressionMethods(int method, int level) const;
    virtual const int *getFilters() const;
    virtual int getStrategy(Filter &);

    virtual void pack(OutputFile *fo);
    virtual void unpack(OutputFile *fo);

    virtual bool canPack();
    virtual int canUnpack();

protected:
    virtual Elf_LE64_Shdr const *getElfSections();
    virtual void buildLoader(const Filter *ft);
    virtual Linker* newLinker() const;
};


#endif /* already included */


/*
vi:ts=4:et
*/

