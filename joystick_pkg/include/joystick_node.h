 #pragma once
 #include <stdint.h>
 struct JSevent
    {

    enum etype: std::uint8_t{    button=1,    axis=2};

	uint32_t time;	/* event timestamp in milliseconds */
	int16_t value;	/* value */
	etype type;	/* event type */
	uint8_t number;	/* axis/button number */
    
    
    };