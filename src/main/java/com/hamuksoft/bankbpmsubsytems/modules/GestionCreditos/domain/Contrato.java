package com.hamuksoft.bankbpmsubsytems.modules.GestionCreditos.domain;

import lombok.Builder;
import lombok.Getter;

@Getter
@Builder
public class Contrato {
    private String contratoId;
    private String monto;
    private String fechaInicio;
    private String fechaFin;
    private String intereses;
}
