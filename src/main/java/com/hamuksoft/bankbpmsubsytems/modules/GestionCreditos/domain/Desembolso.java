package com.hamuksoft.bankbpmsubsytems.modules.GestionCreditos.domain;

import lombok.Builder;
import lombok.Getter;

@Getter
@Builder
public class Desembolso {
    private String desembolsoId;
    private double montoDesembolso;
    private String cuentaDestino;
    private String fechaDesembolso;
}
