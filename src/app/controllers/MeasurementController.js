import * as Yup from 'yup';

import Measurement from '../models/Measurement';
import Sensor from '../models/Sensor';
import Word from '../models/Word';

class MeasurementController {
  async index(req, res) {
    const { sensor_id, word } = req.query;
    const measurements = await Measurement.findAll({
      where: { sensor_id, word },
      attributes: ['value', 'created_at'],
      order: [['created_at', 'DESC']],
    });

    const searchSensor = await Sensor.findOne({
      where: { sensor_id },
      attributes: ['name', 'type'],
    });

    const searchWord = await Word.findOne({
      where: { sensor_id },
      attributes: ['name', 'alarm'],
    });

    return res.json({ measurements, sensor: searchSensor, word: searchWord });
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
