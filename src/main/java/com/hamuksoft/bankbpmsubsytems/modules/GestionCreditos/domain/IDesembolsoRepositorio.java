package com.hamuksoft.bankbpmsubsytems.modules.GestionCreditos.domain;

import java.util.List;

public interface IDesembolsoRepositorio {
    Desembolso guardar(Desembolso desembolso);
    Desembolso buscarDesembolso(String desembolsoId);
    List<Desembolso> listarDesembolsos();
    void eliminarDesembolso(String desembolsoId);
    List<Desembolso> buscarDesembolsosPorCredito(String creditoId);
}
