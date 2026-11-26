# AIR-QUALITY — Nodo IoT de Monitoreo 

Sistema embebido compacto (**50,64 mm**) basado en **ESP32** para la detección, acondicionamiento y telemetría de gases inflamables y monóxido de carbono.

<p align="center">
  <img src="3D/PCB_3d.png" alt="Vista 3D PCB AIR-QUALITY" width="320">
</p>

## Resumen de Ingeniería
* **Unidad de Procesamiento y RF:** Módulo ESP32 con zonificación topológica por cuadrantes y área *keep-out* libre de cobre bajo la antena impresa para preservar la impedancia característica ($Z_0 = 50\,\Omega$).
* **Etapa de Sensado:** Integración de sensores semiconductores **MQ-2** (GLP, humo, propano) y **MQ-7** (monóxido de carbono).
* **Acondicionamiento Analógico:** Divisores resistivos de precisión (relación 1:2) para adaptación de rango e impedancia hacia el ADC del ESP32, logrando un error experimental $\le 4\text{ mV}$ en el rango de $1\text{--}5\text{ V}$.
* **Gestión de Potencia y Eficiencia:** Regulación lineal mediante **AMS1117-3.3** ($T_J \approx 78,55\,^\circ\text{C}$, rizado $< 12\text{ mV}_{\text{PP}}$) y conmutación *low-side* por MOSFET para el control energético de los calefactores de los sensores.

## Estructura del Repositorio
* **`3D/`:** Renderizado 3D de la tarjeta (`PCB_3d.png`) y planos físicos (`PCB_AIR_QUALITY.pdf`).
* **`ALTIUM_FILES/`:** Archivos nativos de diseño PCB, librerías y salidas de fabricación en Altium Designer.
* **`SCH/`:** Esquemáticos eléctricos jerárquicos del sistema.
* **`Archivos_Finales/`:** Entregables consolidados del proyecto.
* **Documentación y Evidencias:** Presentación ejecutiva (`AIR-QUALITY PST-Luis David Duque Cañas-1.pdf`) y montaje experimental en protoboard (`poc_proto.jp.jpeg`).
