#include "protocolparser.h"

ProtocolParser::ProtocolParser(QObject* parent)
    : QObject(parent), m_state(WAIT_CTRL) {}

void ProtocolParser::feed(const QByteArray& data) {
    for (quint8 byte : data) {
        switch (m_state) {

        case WAIT_CTRL:
            m_ctrl = byte;
            m_state = WAIT_LEN;
            break;

        case WAIT_LEN:
            m_len = byte;
            m_payload.clear();
            m_state = WAIT_DATA;
            break;

        case WAIT_DATA:
            m_payload.append(byte);
            if (m_payload.size() == m_len) {
                // -------- DISPATCH ----------
                switch (m_ctrl) {
			case 0xF5: { // NIBP
    			int sys = (static_cast<quint8>(m_payload[1]) << 8) |
               		static_cast<quint8>(m_payload[2]);
    			int dia = static_cast<quint8>(m_payload[3]);
    			int mean = (m_len == 6) ? static_cast<quint8>(m_payload[4]) : 0;
    			emit nibp(sys, dia, mean);
    			break;
			}

			case 0xF8: { // Weight
    			float w = static_cast<quint8>(m_payload[0]) +
              		static_cast<quint8>(m_payload[1]) / 10.0f;
    			emit weight(w);
   			break;
			}

			case 0xF7: { // Height
    			emit height(static_cast<quint8>(m_payload[0]));
    			break;
			}

                /*
                case 0xF2: // Pulse
                    //emit pulseUpdated(m_payload[0]);
		    emit pulseRate(static_cast<quint8>(m_payload[0]));
                    break;

                case 0xF4: // SPO2
                    //emit spo2Updated(m_payload[0]);
		    emit spo2(static_cast<quint8>(m_payload[0]));
                    break;

                case 0xFA: { // Temperature
                    //int dec = m_payload[0];
                    //int frac = m_payload[1];
		    int dec = static_cast<quint8>(m_payload[0]);
                    int frac = static_cast<quint8>(m_payload[1]);
                    float temp = dec + (frac / 10.0f);
                    emit temperatureUpdated(temp);
                    break;
                }

                case 0xF5: { // NIBP
                    int sys = (m_payload[1] << 8) | m_payload[2];
                    int dia = m_payload[3];
                    int mean = (m_len == 6) ? m_payload[4] : 0;
                    emit nibpUpdated(sys, dia, mean);
                    break;
                }

                case 0xF8: { // Weight
                    float w = m_payload[0] + (m_payload[1] / 10.0f);
                    emit weightUpdated(w);
                    break;
                }

                case 0xF7:
                    emit heightUpdated(m_payload[0]);
                    break;
                }
                */
	}
                m_state = WAIT_CTRL;
            }
            break;
        }
    }
}

