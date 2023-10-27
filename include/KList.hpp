/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-10-24.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *  3. All advertising materials mentioning features or use of this software
 *  must display the following acknowledgement:
 *  This product includes software developed by the SJ Group. and
 *  its contributors.
 *  4. Neither the name of the Group nor the names of its contributors may
 *  be used to endorse or promote products derived from this software
 *  without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY SongJian, GROUP AND CONTRIBUTORS
 *  ===================================================================
 * @file KList.h
 * @author KSJ
 * @date 2023-10-24
 * @version 0.0.2
 * @brief 全面升级，使用cpp构建的list<T>
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#pragma once
#include<base.h>
#include<concepts>
#include<vector>
#include<memory>
#include<Iter.hpp>
#include<cassert>
/**
 * @author SJ
 * @date 2023-10-26
 * @class NativeList<T>
 * @brief 原始列表类
 * @param[in] T 数据域的类型
 * @bug no bug found
 * @warning no warning
 * @todo no todo
 * @exception no exception
*/
template<typename T>
requires ExistDefaultConstruction<T>
class __declspec(dllexport) NativeList{
 public:
    NativeList();
    ~NativeList();
    explicit NativeList(const T& data);
    virtual const T& getData()const;
    virtual T& getData();
    virtual NativeList<T>* getNext();
 public:
    NativeList<T>* pre;
    NativeList<T>* nxt;
    T data;
};
/**
 * @author SJ
 * @date 2023-10-26
 * @class KList<T>
 * @brief 链表集成
 * @tparam[in] T 数据域类型
 * @bug[1] if erase all, the cur will be nullptr then work is abnormal
 * @warning now, we shouldn't erase all element
 * @todo may we should guarantee that it will work in length is 0
*/
template<typename T>
class __declspec(dllexport) KList{
 public:
    KList();
    ~KList() = default;
    explicit KList(T data);
    /**
     * @brief 链表后移
     * @author SJ
     * @return true 成功
     * @return false 下一个为空
     */
    virtual bool toNext();
    /**
     * @brief 链表前移
     * @author SJ
     * @return true 成功
     * @return false 失败
     */
    virtual bool toPre();
    /**
     * @brief Get the Data object
     * @author SJ
     * @return const T&
     */
    virtual const T& getData()const;
    /**
     * @brief Set the Data object
     * @author SJ
     * @param data
     */
    virtual void setData(const T& data)const;
    /**
     * @brief Get the Cur object
     * @author SJ
     * @return const NativeList* point current
     */
    virtual const NativeList<T>* getCur()const;
    /**
     * @brief 直接跳转到目的指针，目前不检验合法性
     * @author SJ
     * @param pos 目的指针
     * @warning 请自行保证pos的合法性
     */
    virtual void gotoP(const NativeList<T>* pos);
    /**
     * @brief 在pos后插入新节点
     * @author SJ
     * @param pos 指针
     * @param data 数据
     */
    virtual void insertBack(NativeList<T>* pos, const T& data);
    /**
     * @brief 在指定位置之前插入新节点
     * @author SJ
     * @param pos 指针
     * @param data 数据
     */
    virtual void insertPre(NativeList<T>* pos, const T& data);
    /**
     * @brief 在当前节点后插入
     * @author SJ
     * @param data insert data
     */
    virtual void insertBack(const T& data);
    /**
     * @brief 在当前节点后插入
     * @author SJ
     * @param data insert data
     */
    virtual void insertPre(const T& data);
    /**
     * @brief ++List<T>
     * @author SJ
     * @return true
     * @return false
     */
    virtual bool operator++();
    /**
     * @brief List<T++
     * @fn
     * @return true
     * @return false
     */
    virtual bool operator++(int);
    /**
     * @brief --List<T>
     *
     * @return true
     * @return false
     */
    virtual bool operator--();
    /**
     * @brief List<T>--
     *
     * @return true
     * @return false
     */
    virtual bool operator--(int);
    /**
     * @brief 返回首迭代器
     *
     * @return Iter<NativeList<T>, T>
     */
    virtual Iter<NativeList<T>*, T> begin();
    /**
     * @brief 返回尾迭代器
     *
     * @return Iter<NativeList<T>, T>
     */
    virtual Iter<NativeList<T>*, T> end();
    /**
     * @brief Get the Length object
     * @author SJ
     * @return const size_t
     */
    virtual const size_t getLength()const;
    /**
     * @brief delete pos from KList<T>
     * @author SJ
     * @param pos the pointer of what you wanna delete
     * @warning if pos==cur, default,cur will goNext, if failed , then will goPre
     *  if both failed, the cur will be nullptr, which is danger
     */
    virtual void erase(NativeList<T>* pos);
    /**
     * @brief erase current
     */
    virtual void erase();
    /**
     * @brief Get the Pre object
     * @author SJ
     * @return const NativeList<T>*
     */
    virtual const NativeList<T>* getPre()const;
    /**
     * @brief Get the Nxt object
     * @author SJ
     * @return const NativeList<T>*
     */
    virtual const NativeList<T>* getNxt()const;
    virtual const NativeList<T>* getHead()const;
 private:
    NativeList<T>* cur;
    NativeList<T>* head;
    size_t length;
};


template <typename T>
KList<T>::KList() {
    this->cur = new NativeList<T>();
    this->head = this->cur;
}

template <typename T>
KList<T>::KList(T data) : KList<T>() {
    this->cur->data = data;
    this->length = 1;
}

template <typename T>
bool KList<T>::toNext() {
    if (nullptr == this->cur->nxt)return false;
    this->cur = this->cur->nxt;
    return true;
}

template <typename T>
bool KList<T>::toPre() {
    if (nullptr == this->cur->pre)return false;
    this->cur = this->cur->pre;
    return true;
}

template <typename T>
const T &KList<T>::getData() const {
    return this->cur->data;
}

template<typename T>
void KList<T>::setData(const T & data) const {
    this->cur->data = data;
}

template<typename T>
const NativeList<T> * KList<T>::getCur() const {
    return this->cur;
}

template<typename T>
void KList<T>::gotoP(const NativeList<T>* pos) {
    this->cur =  const_cast<NativeList<T>*>(pos);
}

template<typename T>
void KList<T>::insertBack(NativeList<T>* pos, const T & data) {
    auto tmp = new NativeList<T>(data);
    tmp->pre = pos;
    tmp->nxt = pos->nxt;
    if (pos->nxt)pos->nxt->pre = tmp;
    pos->nxt = tmp;
    this->length++;
}

template<typename T>
void KList<T>::insertPre(NativeList<T>* pos, const T & data) {
    if (pos->pre) {
        this->insertBack(pos->pre, data);
    } else {
        auto tmp = new NativeList<T>(data);
        tmp->nxt = pos;
        pos->pre = tmp;
        this->length++;
    }
    if (this->head == pos)this->head = pos->pre;
}

template<typename T>
void KList<T>::insertBack(const T& data) {
    this->insertBack(this->cur, data);
}

template<typename T>
void KList<T>::insertPre(const T & data) {
    if (this->cur->pre)this->insertPre(this->cur, data);
}

template <typename T>
bool KList<T>::operator++() {
    return this->toNext();
}

template <typename T>
bool KList<T>::operator++(int) {
    return this->toNext();
}

template <typename T>
bool KList<T>::operator--() {
    return this->toPre();
}

template <typename T>
bool KList<T>::operator--(int) {
    return this->toPre();
}

template <typename T>
inline Iter<NativeList<T>*, T> KList<T>::begin() {
    return Iter<NativeList<T>*, T>(this->head);
}

template<typename T>
inline Iter<NativeList<T>*, T> KList<T>::end() {
    return Iter<NativeList<T>*, T>(nullptr);
}
template <typename T>
inline const size_t KList<T>::getLength() const {
    return this->length;
}

template <typename T>
inline void KList<T>::erase(NativeList<T> *pos) {
    assert(pos != nullptr);
    if (pos->pre) pos->pre->nxt = pos->nxt;
    if (pos->nxt) pos->nxt->pre = pos->pre;
    if (pos == this->cur) {
        if (!this->toNext())
            if (!this->toPre())
                PrintErr("ERROR", "KList<T> is null");
    }
    delete pos;
    pos = nullptr;
    this->length--;
}
template <typename T>
inline void KList<T>::erase() {
    this->erase(this->cur);
}
template <typename T>
inline const NativeList<T> *KList<T>::getPre() const {
    return this->cur->pre;
}
template <typename T>
inline const NativeList<T> *KList<T>::getNxt() const {
    return this->cur->nxt;
}
template <typename T>
inline const NativeList<T> *KList<T>::getHead() const {
    return this->head;
}
template <typename T>
    requires ExistDefaultConstruction<T>
NativeList<T>::NativeList()
{
    this->pre = nullptr;
    this->nxt = nullptr;
    this->data = T();
}

template <typename T>
requires ExistDefaultConstruction<T>
NativeList<T>::~NativeList() {
    /// @attention maybe shouldn't delete them in KList<T>?
    // if (this->pre) delete this->pre;
    // if (this->nxt) delete this->nxt;
    this->pre = nullptr;
    this->nxt = nullptr;
}

template<typename T>
requires ExistDefaultConstruction<T>
NativeList<T>::NativeList(const T& data) : NativeList<T>() {
    this->data = data;
}

template <typename T>
requires  ExistDefaultConstruction<T>
inline const T &NativeList<T>::getData() const {
    return this->data;
}

template <typename T>
requires  ExistDefaultConstruction<T>
inline T &NativeList<T>::getData() {
    return this->data;
}
template <typename T>
requires ExistDefaultConstruction<T>
inline NativeList<T> *NativeList<T>::getNext() {
    return this->nxt;
}
