import * as Yup from 'yup';

import Sensor from '../models/Sensor';

class SensorController {
  async index(req, res) {
    const sensors = await Sensor.findAll();

    return res.json(sensors);
  }

  async store(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      name: Yup.string().required(),
      description: Yup.string().required(),
      type: Yup.string().required(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações invalidas' });
    }

    const sensorExists = await Sensor.findOne({
      where: { sensor_id: req.body.sensor_id },
    });

    if (sensorExists) {
      return res
        .status(401)
        .json({ error: 'Sensor já cadastrado anteriormente' });
    }
    const { sensor_id, name, description, type } = await Sensor.create(
      req.body
    );

    return res.json({
      sensor_id,
      name,
      description,
      type,
    });
  }

  async update(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      name: Yup.string(),
      description: Yup.string(),
      type: Yup.string(),
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

    const { sensor_id, name, description, type } = req.body;

    const sensor_update = await sensor.update({
      sensor_id,
      name,
      description,
      type,
    });

    return res.json({
      sensor_id: sensor_update.sensor_id,
      name: sensor_update.name,
      description: sensor_update.description,
      type: sensor_update.type,
    });
  }
}

export default new SensorController();
