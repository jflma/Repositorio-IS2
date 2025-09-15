package com.hamuksoft.bankbpmsubsytems.modules.GestionCreditos.domain;

import lombok.Builder;
import lombok.Getter;

@Getter
@Builder
public class Credito {
    private String creditoId;
    private String contratoId;
    private String clienteId;
    private String desembolsoId;
    private String monto;
}
