/*
 * BIT_MATH.h
 *
 * Created: 8/27/2022 1:06:16 PM
 *  Author: AbdelRaHmaN ShRieF
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*

SET_BIT

This macro used to set a pin value as (1) at index (BIT) in register 

*/
#define SET_BIT(REG,BIT) (REG |= (1<<BIT) )

/*

CLR_BIT

This macro used to set a pin value as (0) at index (BIT) in register 

*/
#define CLR_BIT(REG,BIT) (REG &= ~(1<<BIT))

/*

GET_BIT

This macro used to Get a pin value at index (BIT) in register 

*/
#define GET_BIT(REG,BIT) (REG>>BIT & 1 )

/*
TOG_BIT

This macro used to toggle pin value at index (BIT) in register 

*/
#define TOG_BIT(REG,BIT) (REG ^= (1<<BIT))


#endif /* BIT_MATH_H_ */