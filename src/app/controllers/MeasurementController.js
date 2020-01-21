import * as Yup from 'yup';

import Measurement from '../models/Measurement';
import Sensor from '../models/Sensor';

class MeasurementController {
  async index(req, res) {
    const { sensor_id, word } = req.query;
    const measurements = await Measurement.findAll({
      where: { sensor_id, word },
      attributes: ['value', 'created_at'],
      order: [['created_at', 'DESC']],
    });

    const { name, type } = await Sensor.findOne({
      where: { sensor_id },
      attributes: ['name', 'type'],
    });
    return res.json({ measurements, name, type });
  }

  async store(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      word: Yup.number().required(),
      value: Yup.string().required(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações Invalidas' });
    }

    const { sensor_id, word, value } = await Measurement.create(req.body);

    return res.json({ sensor_id, word, value });
  }
}

export default new MeasurementController();
