MODULE ADMM_TAPENADE_INTERFACE
  IMPLICIT NONE
  INTERFACE PUSHPOINTER8
      SUBROUTINE PUSHPOINTER8(pp) BIND(c, name='pushpointer8')
        USE ISO_C_BINDING
        TYPE(C_PTR), VALUE :: pp
      END SUBROUTINE PUSHPOINTER8
  END INTERFACE PUSHPOINTER8

  INTERFACE LOOKPOINTER8
      SUBROUTINE LOOKPOINTER8(pp) BIND(c, name='lookpointer8')
        USE ISO_C_BINDING
        TYPE(C_PTR) :: pp
      END SUBROUTINE LOOKPOINTER8
  END INTERFACE LOOKPOINTER8

  INTERFACE POPPOINTER8
      SUBROUTINE POPPOINTER8(pp) BIND(c, name='poppointer8')
        USE ISO_C_BINDING
        TYPE(C_PTR) :: pp
      END SUBROUTINE POPPOINTER8
  END INTERFACE POPPOINTER8

  INTERFACE ADMM_REGISTERSHADOWED
      SUBROUTINE ADMM_REGISTERSHADOWED(base, obase, size, baseb, obaseb&
&       , sizeb, nbelem) BIND(c, name='ADMM_RegisterShadowed')
        USE ISO_C_BINDING
        TYPE(C_PTR), VALUE :: base, obase
        TYPE(C_PTR), VALUE :: baseb, obaseb
        INTEGER, VALUE :: size, sizeb
        INTEGER, VALUE :: nbelem
      END SUBROUTINE ADMM_REGISTERSHADOWED
  END INTERFACE ADMM_REGISTERSHADOWED

  INTERFACE ADMM_REGISTER
      SUBROUTINE ADMM_REGISTER(base, obase, size, nbelem) BIND(c, name=&
&     'ADMM_Register')
        USE ISO_C_BINDING
        TYPE(C_PTR), VALUE :: base, obase
        INTEGER, VALUE :: size
        INTEGER, VALUE :: nbelem
      END SUBROUTINE ADMM_REGISTER
  END INTERFACE ADMM_REGISTER

  INTERFACE ADMM_UNREGISTERSHADOWED
      SUBROUTINE ADMM_UNREGISTERSHADOWED(base, baseb, nbelem) BIND(c, &
&     name='ADMM_UnregisterShadowed')
        USE ISO_C_BINDING
        TYPE(C_PTR), VALUE :: base, baseb
        INTEGER :: nbelem
      END SUBROUTINE ADMM_UNREGISTERSHADOWED
  END INTERFACE ADMM_UNREGISTERSHADOWED

  INTERFACE ADMM_UNREGISTER
      SUBROUTINE ADMM_UNREGISTER(base, nbelem) BIND(c, name=&
&     'ADMM_Unregister')
        USE ISO_C_BINDING
        TYPE(C_PTR), VALUE :: base
        INTEGER :: nbelem
      END SUBROUTINE ADMM_UNREGISTER
  END INTERFACE ADMM_UNREGISTER

  INTERFACE ADMM_REBASESHADOWED
      SUBROUTINE ADMM_REBASESHADOWED(base, baseb) BIND(c, name=&
&     'ADMM_RebaseShadowed')
        USE ISO_C_BINDING
        TYPE(C_PTR) :: base, baseb
      END SUBROUTINE ADMM_REBASESHADOWED
  END INTERFACE ADMM_REBASESHADOWED

  INTERFACE ADMM_REBASE
      SUBROUTINE ADMM_REBASE(base) BIND(c, name='ADMM_Rebase')
        USE ISO_C_BINDING
        TYPE(C_PTR) :: base
      END SUBROUTINE ADMM_REBASE
  END INTERFACE ADMM_REBASE

END MODULE ADMM_TAPENADE_INTERFACE

