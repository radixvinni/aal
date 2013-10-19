cmake_minimum_required(VERSION 2.8)
project(Miracl)
include_directories (miracl/include/)
include_directories (miracl/)
set (MIRACL
	miracl/source/big.cpp
	miracl/source/crt.cpp
	miracl/source/curve/complex.cpp
	miracl/source/curve/flpoly.cpp
	miracl/source/curve/modpol.cpp
	miracl/source/curve/poly.cpp
	miracl/source/curve/poly2.cpp
	miracl/source/curve/poly2mod.cpp
#	miracl/source/curve/poly2xy.cpp
	miracl/source/curve/polymod.cpp
	miracl/source/curve/polyxy.cpp
	miracl/source/curve/ps_zzn.cpp
	miracl/source/curve/schoof.cpp
	miracl/source/curve/schoof2.cpp
	miracl/source/curve/sea.cpp
	miracl/source/ec2.cpp
	miracl/source/ecn.cpp
	miracl/source/ecnzzn.cpp
	miracl/source/flash.cpp
	miracl/source/floating.cpp
	miracl/source/gf2m.cpp
	miracl/source/mr87f.c
	miracl/source/mr87v.c
	miracl/source/mraes.c
	miracl/source/mralloc.c
	miracl/source/mrarth0.c
	miracl/source/mrarth1.c
	miracl/source/mrarth2.c
	miracl/source/mrarth3.c
	miracl/source/mrbits.c
	miracl/source/mrbrick.c
	miracl/source/mrbuild.c
	miracl/source/mrcore.c
	miracl/source/mrcrt.c
	miracl/source/mrcurve.c
	miracl/source/mrdouble.c
	miracl/source/mrebrick.c
	miracl/source/mrec2m.c
	miracl/source/mrecn2.c
	miracl/source/mrfast.c
	miracl/source/mrflash.c
	miracl/source/mrflsh1.c
	miracl/source/mrflsh2.c
	miracl/source/mrflsh3.c
	miracl/source/mrflsh4.c
	miracl/source/mrfrnd.c
	miracl/source/mrgcd.c
	miracl/source/mrgcm.c
	miracl/source/mrgf2m.c
	miracl/source/mrio1.c
	miracl/source/mrio2.c
	miracl/source/mrjack.c
	miracl/source/mrlucas.c
	miracl/source/mrmonty.c
	miracl/source/mrmuldv.c
	miracl/source/mrpi.c
	miracl/source/mrpower.c
	miracl/source/mrprime.c
	miracl/source/mrrand.c
	miracl/source/mrround.c
	miracl/source/mrscrt.c
	miracl/source/mrshs.c
	miracl/source/mrshs256.c
	miracl/source/mrshs512.c
	miracl/source/mrsmall.c
	miracl/source/mrsroot.c
	miracl/source/mrstrong.c
	miracl/source/mrxgcd.c
	miracl/source/mrzzn2.c
	miracl/source/mrzzn2b.c
	miracl/source/mrzzn3.c
	miracl/source/zzn.cpp
)
configure_file(miracl/source/mrmuldv.ccc ../miracl/source/mrmuldv.c)
if (MSVC)
	configure_file(miracl/include/mirdef.ccc ../miracl/include/mirdef.h)
  add_definitions (/W0)
elseif (CMAKE_COMPILER_IS_GNUCXX)
 	configure_file(miracl/include/mirdef.lnx ../miracl/include/mirdef.h)
  add_definitions (-w)
endif (MSVC)
add_library (Miracl ${MIRACL})
