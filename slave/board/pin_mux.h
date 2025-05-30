/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (number 62), U7[4]/UART0_RX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTB                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 16U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN_MASK (1U << 16U)      /*!<@brief PORT pin mask */
                                                               /* @} */

/*! @name PORTB17 (number 63), U10[1]/UART0_TX
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTB                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 17U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN_MASK (1U << 17U)      /*!<@brief PORT pin mask */
                                                               /* @} */

/*! @name PORTE24 (number 31), J2[20]/U8[4]/I2C0_SCL
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ACCEL_SCL_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ACCEL_SCL_PIN 24U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ACCEL_SCL_PIN_MASK (1U << 24U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*! @name PORTE25 (number 32), J2[18]/U8[6]/I2C0_SDA
  @{ */

/* Symbols to be used with PORT driver */
#define BOARD_INITPINS_ACCEL_SDA_PORT PORTE                /*!<@brief PORT peripheral base pointer */
#define BOARD_INITPINS_ACCEL_SDA_PIN 25U                   /*!<@brief PORT pin number */
#define BOARD_INITPINS_ACCEL_SDA_PIN_MASK (1U << 25U)      /*!<@brief PORT pin mask */
                                                           /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
