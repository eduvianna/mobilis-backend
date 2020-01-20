import * as Yup from 'yup';

import Sensor from '../models/Sensor';

class SensorController {
  async store(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      name: Yup.string().required(),
      description: Yup.string().required(),
      type: Yup.string().required(),
      word: Yup.number().required(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações invalidas' });
    }

    const wordInUse = await Sensor.findOne({
      where: { sensor_id: req.body.sensor_id, word: req.body.word },
    });

    if (wordInUse) {
      return res
        .status(400)
        .json({ error: 'Está palavra já está em uso com este ID' });
    }

    const { sensor_id, name, description, type, word } = await Sensor.create(
      req.body
    );

    return res.json({ sensor_id, name, description, type, word });
  }

  async update(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      name: Yup.string(),
      description: Yup.string(),
      type: Yup.string(),
      word: Yup.string(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações invalidas' });
    }

    const sensor = await Sensor.findOne({
      where: { sensor_id: req.body.sensor_id },
    });

    if (!sensor) {
      return res.status(401).json({ error: 'Sensor não encontrado' });
    }

    const { sensor_id, name, description, type, word } = req.body;

    if (word) {
      const wordInUse = await Sensor.findOne({
        where: { sensor_id: req.body.sensor_id, word: req.body.word },
      });

      if (wordInUse) {
        return res
          .status(400)
          .json({ error: 'Está palavra já está em uso com este ID' });
      }
    }

    const sensor_update = await sensor.update({
      sensor_id,
      name,
      description,
      type,
      word,
    });

    return res.json({
      sensor_id: sensor_update.sensor_id,
      name: sensor_update.name,
      description: sensor_update.description,
      type: sensor_update.type,
      word: sensor_update.word,
    });
  }
}

export default new SensorController();
