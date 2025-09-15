package com.hamuksoft.bankbpmsubsytems.modules.GestionCreditos.domain;

import java.util.List;
import java.util.Optional;

public interface ICreditoRepositorio {
    Credito guardar(Credito credito);
    Optional<Credito> buscarCredito(String creditoId);
    List<Credito>  listarCreditos();
    void eliminarCredito(String creditoId);
    List<Credito> buscarCreditosPorCliente(String clienteId);
}
