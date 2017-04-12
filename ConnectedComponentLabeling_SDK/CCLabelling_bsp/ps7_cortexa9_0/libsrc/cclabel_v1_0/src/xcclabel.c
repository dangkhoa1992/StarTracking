// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2014.4
// Copyright (C) 2014 Xilinx Inc. All rights reserved.
// 
// ==============================================================

/***************************** Include Files *********************************/
#include "xcclabel.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCclabel_CfgInitialize(XCclabel *InstancePtr, XCclabel_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Crtls_BaseAddress = ConfigPtr->Crtls_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCclabel_Start(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL) & 0x80;
    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCclabel_IsDone(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCclabel_IsIdle(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCclabel_IsReady(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCclabel_EnableAutoRestart(XCclabel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL, 0x80);
}

void XCclabel_DisableAutoRestart(XCclabel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_CTRL, 0);
}

u32 XCclabel_Get_return(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_AP_RETURN);
    return Data;
}
void XCclabel_Set_imgHeight(XCclabel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IMGHEIGHT_DATA, Data);
}

u32 XCclabel_Get_imgHeight(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IMGHEIGHT_DATA);
    return Data;
}

void XCclabel_Set_imgWidth(XCclabel *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IMGWIDTH_DATA, Data);
}

u32 XCclabel_Get_imgWidth(XCclabel *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IMGWIDTH_DATA);
    return Data;
}

void XCclabel_InterruptGlobalEnable(XCclabel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_GIE, 1);
}

void XCclabel_InterruptGlobalDisable(XCclabel *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_GIE, 0);
}

void XCclabel_InterruptEnable(XCclabel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IER);
    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IER, Register | Mask);
}

void XCclabel_InterruptDisable(XCclabel *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IER);
    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IER, Register & (~Mask));
}

void XCclabel_InterruptClear(XCclabel *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCclabel_WriteReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_ISR, Mask);
}

u32 XCclabel_InterruptGetEnabled(XCclabel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_IER);
}

u32 XCclabel_InterruptGetStatus(XCclabel *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCclabel_ReadReg(InstancePtr->Crtls_BaseAddress, XCCLABEL_CRTLS_ADDR_ISR);
}
