/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "std_dev_impl.h"

namespace gr {
  namespace AMR {

    std_dev::sptr
    std_dev::make(int vlen)
    {
      return gnuradio::get_initial_sptr
        (new std_dev_impl(vlen));
    }

    /*
     * The private constructor
     */
    std_dev_impl::std_dev_impl(int vlen)
      : gr::sync_block("std_dev",
              gr::io_signature::make(1, 1, sizeof(float)*vlen),
              gr::io_signature::make(1, 1, sizeof(float))),
        p_vlen(vlen)
    {
        set_max_noutput_items(1);
    }

    /*
     * Our virtual destructor.
     */
    std_dev_impl::~std_dev_impl()
    {
    }

    int
    std_dev_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];

        float mean = 0;
        for (int i = 0; i < p_vlen; i++)
        {
            mean += in[i];
        }
        mean = mean/p_vlen;

        float std_dev = 0;
        for (int i = 0; i < p_vlen; i++)
        {
            std_dev = std_dev + pow(in[i] - mean,2);
        }
        std_dev = sqrt(std_dev/p_vlen);

        *out = std_dev;   

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace AMR */
} /* namespace gr */

