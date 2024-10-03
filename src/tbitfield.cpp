// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);


TBitField::TBitField(int len){
if(len < 0) throw ("size_of_tbitfield_negative");
	BitLen = len;
    MemLen = (TELEM)len / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr) throw ("memory_allocation_error");
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{ BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr) throw ("memory_allocation_error");
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField(){
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
if(n < 0) throw ("negative_index");
     return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
if(n < 0) throw ("negative_index");
   return TELEM(1) << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
if((n < 0) || (n >= BitLen)) 
	throw ("negative_index"); 
pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n){ // очистить бит
if((n < 0) || (n >= BitLen)) 
	throw ("negative_index");
pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
if((n < 0) || (n >= BitLen)) 
	throw ("negative_index");
  if (pMem[GetMemIndex(n)] & GetMemMask(n)) return 1;
    else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (*this == bf) return *this;
    if (MemLen == bf.MemLen) {
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
        return *this;
    }
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr) throw ("memory_allocation_error");
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{   if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen)) return 0;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this == bf) return 0;
    else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField Temp(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Temp.pMem[i] = bf.pMem[i] | pMem[i];
    for (int i = min(MemLen, bf.MemLen); i < max(MemLen, bf.MemLen); i++)
        if (BitLen > bf.BitLen) Temp.pMem[i] = pMem[i];
        else Temp.pMem[i] = bf.pMem[i];
    return Temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField Temp(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        Temp.pMem[i] = bf.pMem[i] & pMem[i];
    return Temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField Temp(BitLen);
    for (int i = 0; i < Temp.MemLen; i++)
        Temp.pMem[i] = ~pMem[i];
    if(Temp.MemLen * 8 * sizeof(TELEM) != Temp.BitLen)
        Temp.pMem[MemLen - 1] &= (((TELEM)1 << Temp.BitLen % (sizeof(TELEM) * 8)) - 1);
    return Temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string str;
    istr >> str;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '1') bf.SetBit(i);
        if(str[i] == '0') bf.ClrBit(i);
        if ((str[i] != '0') && (str[i] != '1')) throw ("wrong_element_input");
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
