/*
 * Some or all of this work - Copyright (c) 2006 - 2017, Intel Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * Neither the name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Resource Descriptor macros
 *
 * PinGroupConfig Resource Descriptor Macro
 */

Name (P464, Package() {
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x00 /* Default */, 0x1000, "\\_SB.GPO2", 0x0,
                       "group0", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x01 /* Bias Pull-up */, 0x2000, "\\_SB.GPO2", 0x0,
                       "group1", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x02 /* Bias Pull-down */, 0x3000, "\\_SB.GPO2", 0x0,
                       "group2", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x03 /* Bias Default */, 0x4000, "\\_SB.GPO2", 0x0,
                       "group3", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x04 /* Bias Disable */, 0x5000, "\\_SB.GPO2", 0x0,
                       "group4", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x05 /* Bias High Impedance */, 0x6000, "\\_SB.GPO2", 0x0,
                       "group5", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x06 /* Bias Bus Hold */, 0x7000, "\\_SB.GPO2", 0x0,
                       "group6", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x07 /* Drive Open Drain */, 0x8000, "\\_SB.GPO2", 0x0,
                       "group7", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x08 /* Drive Open Source */, 0x9000, "\\_SB.GPO2", 0x0,
                       "group8", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x09 /* Drive Push Pull */, 0xa000, "\\_SB.GPO2", 0x0,
                       "group9", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x0a /* Drive Strength */, 0xb000, "\\_SB.GPO2", 0x0,
                       "group10", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x0b /* Slew Rate */, 0xc000, "\\_SB.GPO2", 0x0,
                       "group11", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x0c /* Input Debounce */, 0xd000, "\\_SB.GPO2", 0x0,
                       "group12", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x0d /* Input Schmitt Trigger */, 0xe000, "\\_SB.GPO2", 0x0,
                       "group13", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0x80 /* Vendor defined */, 0xe000, "\\_SB.GPO2", 0x0,
                       "group128", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Exclusive, 0xf0 /* Vendor defined */, 0xf000, "\\_SB.GPO2", 0x0,
                       "group240", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x00 /* Default */, 0x1000, "\\_SB.GPO2", 0x0,
                       "group0", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x01 /* Bias Pull-up */, 0x2000, "\\_SB.GPO2", 0x0,
                       "group1", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x02 /* Bias Pull-down */, 0x3000, "\\_SB.GPO2", 0x0,
                       "group2", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x03 /* Bias Default */, 0x4000, "\\_SB.GPO2", 0x0,
                       "group3", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x04 /* Bias Disable */, 0x5000, "\\_SB.GPO2", 0x0,
                       "group4", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x05 /* Bias High Impedance */, 0x6000, "\\_SB.GPO2", 0x0,
                       "group5", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x06 /* Bias Bus Hold */, 0x7000, "\\_SB.GPO2", 0x0,
                       "group6", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x07 /* Drive Open Drain */, 0x8000, "\\_SB.GPO2", 0x0,
                       "group7", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x08 /* Drive Open Source */, 0x9000, "\\_SB.GPO2", 0x0,
                       "group8", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x09 /* Drive Push Pull */, 0xa000, "\\_SB.GPO2", 0x0,
                       "group9", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x0a /* Drive Strength */, 0xb000, "\\_SB.GPO2", 0x0,
                       "group10", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x0b /* Slew Rate */, 0xc000, "\\_SB.GPO2", 0x0,
                       "group11", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x0c /* Input Debounce */, 0xd000, "\\_SB.GPO2", 0x0,
                       "group12", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x0d /* Input Schmitt Trigger */, 0xe000, "\\_SB.GPO2", 0x0,
                       "group13", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0x80 /* Vendor defined */, 0xe000, "\\_SB.GPO2", 0x0,
                       "group128", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    ResourceTemplate () {
        PinGroupConfig(Shared, 0xf0 /* Vendor defined */, 0xf000, "\\_SB.GPO2", 0x0,
                       "group240", ResourceConsumer,, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    },
    // Minimal
    ResourceTemplate () {
        PinGroupConfig(, 0x01 /* Bias Pull-up */, 0xf000, "\\_SB.GPO2",, "group")
    },
})

Name (P465, Package () {
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00,  /* .&...... */
        /* 0008 */  0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x30, 0x00, 0x0A, 0x0B, 0x0C,  /* oup0.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00,  /* .&...... */
        /* 0008 */  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /*  ....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x00, 0x0A, 0x0B, 0x0C,  /* oup1.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x02, 0x00,  /* .&...... */
        /* 0008 */  0x30, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* 0....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x32, 0x00, 0x0A, 0x0B, 0x0C,  /* oup2.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x03, 0x00,  /* .&...... */
        /* 0008 */  0x40, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* @....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x33, 0x00, 0x0A, 0x0B, 0x0C,  /* oup3.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x04, 0x00,  /* .&...... */
        /* 0008 */  0x50, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* P....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x34, 0x00, 0x0A, 0x0B, 0x0C,  /* oup4.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x05, 0x00,  /* .&...... */
        /* 0008 */  0x60, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* `....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x35, 0x00, 0x0A, 0x0B, 0x0C,  /* oup5.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x06, 0x00,  /* .&...... */
        /* 0008 */  0x70, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* p....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x36, 0x00, 0x0A, 0x0B, 0x0C,  /* oup6.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x07, 0x00,  /* .&...... */
        /* 0008 */  0x80, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x37, 0x00, 0x0A, 0x0B, 0x0C,  /* oup7.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x08, 0x00,  /* .&...... */
        /* 0008 */  0x90, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x38, 0x00, 0x0A, 0x0B, 0x0C,  /* oup8.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x02, 0x00, 0x09, 0x00,  /* .&...... */
        /* 0008 */  0xA0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x39, 0x00, 0x0A, 0x0B, 0x0C,  /* oup9.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x02, 0x00, 0x0A, 0x00,  /* .'...... */
        /* 0008 */  0xB0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x30, 0x00, 0x0A, 0x0B,  /* oup10... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x02, 0x00, 0x0B, 0x00,  /* .'...... */
        /* 0008 */  0xC0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x31, 0x00, 0x0A, 0x0B,  /* oup11... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x02, 0x00, 0x0C, 0x00,  /* .'...... */
        /* 0008 */  0xD0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x32, 0x00, 0x0A, 0x0B,  /* oup12... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x02, 0x00, 0x0D, 0x00,  /* .'...... */
        /* 0008 */  0xE0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x33, 0x00, 0x0A, 0x0B,  /* oup13... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2D)
    {
        /* 0000 */  0x92, 0x28, 0x00, 0x01, 0x02, 0x00, 0x80, 0x00,  /* .(...... */
        /* 0008 */  0xE0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x27, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* '...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x32, 0x38, 0x00, 0x0A,  /* oup128.. */
        /* 0028 */  0x0B, 0x0C, 0x0D, 0x79, 0x00                     /* ...y. */
    },
    Buffer (0x2D)
    {
        /* 0000 */  0x92, 0x28, 0x00, 0x01, 0x02, 0x00, 0xF0, 0x00,  /* .(...... */
        /* 0008 */  0xF0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x27, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* '...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x32, 0x34, 0x30, 0x00, 0x0A,  /* oup240.. */
        /* 0028 */  0x0B, 0x0C, 0x0D, 0x79, 0x00                     /* ...y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00,  /* .&...... */
        /* 0008 */  0x10, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x30, 0x00, 0x0A, 0x0B, 0x0C,  /* oup0.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x01, 0x00,  /* .&...... */
        /* 0008 */  0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /*  ....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x00, 0x0A, 0x0B, 0x0C,  /* oup1.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x02, 0x00,  /* .&...... */
        /* 0008 */  0x30, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* 0....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x32, 0x00, 0x0A, 0x0B, 0x0C,  /* oup2.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x03, 0x00,  /* .&...... */
        /* 0008 */  0x40, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* @....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x33, 0x00, 0x0A, 0x0B, 0x0C,  /* oup3.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x04, 0x00,  /* .&...... */
        /* 0008 */  0x50, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* P....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x34, 0x00, 0x0A, 0x0B, 0x0C,  /* oup4.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x05, 0x00,  /* .&...... */
        /* 0008 */  0x60, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* `....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x35, 0x00, 0x0A, 0x0B, 0x0C,  /* oup5.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x06, 0x00,  /* .&...... */
        /* 0008 */  0x70, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* p....... */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x36, 0x00, 0x0A, 0x0B, 0x0C,  /* oup6.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x07, 0x00,  /* .&...... */
        /* 0008 */  0x80, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x37, 0x00, 0x0A, 0x0B, 0x0C,  /* oup7.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x08, 0x00,  /* .&...... */
        /* 0008 */  0x90, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x38, 0x00, 0x0A, 0x0B, 0x0C,  /* oup8.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2B)
    {
        /* 0000 */  0x92, 0x26, 0x00, 0x01, 0x03, 0x00, 0x09, 0x00,  /* .&...... */
        /* 0008 */  0xA0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x25, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* %...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x39, 0x00, 0x0A, 0x0B, 0x0C,  /* oup9.... */
        /* 0028 */  0x0D, 0x79, 0x00                                 /* .y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x03, 0x00, 0x0A, 0x00,  /* .'...... */
        /* 0008 */  0xB0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x30, 0x00, 0x0A, 0x0B,  /* oup10... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x03, 0x00, 0x0B, 0x00,  /* .'...... */
        /* 0008 */  0xC0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x31, 0x00, 0x0A, 0x0B,  /* oup11... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x03, 0x00, 0x0C, 0x00,  /* .'...... */
        /* 0008 */  0xD0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x32, 0x00, 0x0A, 0x0B,  /* oup12... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2C)
    {
        /* 0000 */  0x92, 0x27, 0x00, 0x01, 0x03, 0x00, 0x0D, 0x00,  /* .'...... */
        /* 0008 */  0xE0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x26, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* &...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x33, 0x00, 0x0A, 0x0B,  /* oup13... */
        /* 0028 */  0x0C, 0x0D, 0x79, 0x00                           /* ..y. */
    },
    Buffer (0x2D)
    {
        /* 0000 */  0x92, 0x28, 0x00, 0x01, 0x03, 0x00, 0x80, 0x00,  /* .(...... */
        /* 0008 */  0xE0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x27, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* '...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x31, 0x32, 0x38, 0x00, 0x0A,  /* oup128.. */
        /* 0028 */  0x0B, 0x0C, 0x0D, 0x79, 0x00                     /* ...y. */
    },
    Buffer (0x2D)
    {
        /* 0000 */  0x92, 0x28, 0x00, 0x01, 0x03, 0x00, 0xF0, 0x00,  /* .(...... */
        /* 0008 */  0xF0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x27, 0x00, 0x04, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* '...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x32, 0x34, 0x30, 0x00, 0x0A,  /* oup240.. */
        /* 0028 */  0x0B, 0x0C, 0x0D, 0x79, 0x00                     /* ...y. */
    },
    Buffer (0x26)
    {
        /* 0000 */  0x92, 0x21, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00,  /* .!...... */
        /* 0008 */  0xF0, 0x00, 0x00, 0x00, 0x14, 0x00, 0x1E, 0x00,  /* ........ */
        /* 0010 */  0x24, 0x00, 0x00, 0x00, 0x5C, 0x5F, 0x53, 0x42,  /* $...\_SB */
        /* 0018 */  0x2E, 0x47, 0x50, 0x4F, 0x32, 0x00, 0x67, 0x72,  /* .GPO2.gr */
        /* 0020 */  0x6F, 0x75, 0x70, 0x00, 0x79, 0x00               /* oup.y. */
    }
})

Method(RT30,, Serialized)
{
    Name(TS, "RT30")

    // Emit test header, set the filename

    THDR (TS, "PinGroupConfig Resource Descriptor Macro", __FILE__)

    // The main test packages must have the same number of entries

    If (LNotEqual (SizeOf (P464), SizeOf (P465)))
    {
        Err (TS, 179, 0, 0, 0, 0, "Incorrect package length")
        Return ()
    }

    // Main test case for packages above

    m330(TS, SizeOf (P464), "P464", P464, P465)

    // Check resource descriptor tag offsets
    Local0 = ResourceTemplate () {
        PinGroupConfig(Shared, 0x01 /* Bias Pull-up */, 0x2000, "\\_SB.GPO2", 0x0, "group0",
                       ResourceConsumer, CFG0, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
        PinGroupConfig(Shared, 0x01 /* Bias Pull-up */, 0x2000, "\\_SB.GPO2", 0x0, "group1",
                       ResourceConsumer, CFG1, RawDataBuffer() {0xa, 0xb, 0xc, 0xd})
    }

    m331(TS, 1, CFG0._SHR, 0x20, CFG1._SHR, 0x168, "_SHR")
    m331(TS, 1, CFG0._TYP, 0x30, CFG1._TYP, 0x178, "_TYP")
    m331(TS, 1, CFG0._VAL, 0x38, CFG1._VAL, 0x180, "_VAL")
    m331(TS, 1, CFG0._VEN, 0x128, CFG1._VEN, 0x270, "_VEN")
}