/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief LPC84X SPI (DMA ��ʽ) �û������ļ�
 * \sa am_hwconf_lpc84x_spi0_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.02 15-11-25  sky, modified
 * - 1.01 15-10-10  aii, second implementation
 * - 1.00 15-07-10  aii, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_gpio.h"
#include "am_lpc_spi_int.h"
#include "am_lpc84x_spi_dma.h"
#include "hw/amhw_lpc84x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_spi0_dma
 * \copydoc am_hwconf_lpc84x_spi0_dma.c
 * @{
 */

/**
 * \brief SPI0 ƽ̨��ʼ��
 */
am_local void __lpc84x_spi0_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIO0_17, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_18, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_19, PIO_FUNC_SPI0_MISO);

    /* CS_Pin ���û����� STD ����ʱ���д��룬�˴��������� */
    amhw_lpc84x_clk_spi0_clk_sel_set (AMHW_LPC84X_CLK_DEVICE_FRG0CLK);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SPI0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SPI0);
}

/**
 * \brief SPI0 ƽ̨���ʼ��
 */
am_local void __lpc84x_spi0_dma_plfm_deinit (void)
{
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SPI0);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_SPI0);

    am_gpio_pin_cfg(PIO0_17, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_18, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_19, AM_GPIO_PULLUP | AM_GPIO_INPUT);
}

/** \brief SPI0 (DMA ��ʽ) �豸��Ϣ */
am_local am_const
struct am_lpc84x_spi_dma_devinfo __g_lpc84x_spi0_dma_devinfo = {
    LPC84X_SPI0_BASE,                /* SPI0 �Ĵ��������ַ */
    CLK_SPI0,                        /* SPI0 ʱ�Ӻ� */
    DMA_CHAN_SPI0_TX_REQ,            /* DMA ����ͨ�� */
    DMA_CHAN_SPI0_RX_REQ,            /* DMA ����ͨ�� */
    AMHW_LPC84X_DMA_CHAN_PRIO_1,     /* �������ȼ� */
    AMHW_LPC84X_DMA_CHAN_PRIO_0,     /* �������ȼ� */
    __lpc84x_spi0_dma_plfm_init,     /* ƽ̨��ʼ������ */
    __lpc84x_spi0_dma_plfm_deinit    /* ƽ̨���ʼ������ */
};

/** \brief SPI0 (DMA ��ʽ) �豸ʵ�� */
am_local am_lpc84x_spi_dma_dev_t __g_lpc84x_spi0_dma_dev;

/**
 * \brief SPI0 (DMA ��ʽ) ʵ����ʼ��
 */
am_spi_handle_t am_lpc84x_spi0_dma_inst_init (void)
{
    return am_lpc84x_spi_dma_init(&__g_lpc84x_spi0_dma_dev,
                                  &__g_lpc84x_spi0_dma_devinfo);
}

/**
 * \brief SPI0 (DMA ��ʽ) ʵ�����ʼ��
 */
void am_lpc84x_spi0_dma_inst_deinit (am_spi_handle_t handle)
{
    am_lpc84x_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */