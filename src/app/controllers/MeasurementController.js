import * as Yup from 'yup';

import Measurement from '../models/Measurement';
import Sensor from '../models/Sensor';
import Word from '../models/Word';

class MeasurementController {
  async index(req, res) {
    const { sensor_id, word } = req.query;
    let measurements = [];
    async function getMeasurements(sensorId, sensorWord) {
      const response = await Measurement.findAll({
        where: { sensor_id: sensorId, word: sensorWord },
        attributes: ['id', 'value', 'created_at'],
        order: [['created_at', 'DESC']],
      });

      const searchSensor = await Sensor.findOne({
        where: { sensor_id: sensorId },
        attributes: ['sensor_id', 'name', 'type'],
      });

      const searchWord = await Word.findOne({
        where: { sensor_id: sensorId },
        attributes: ['name', 'alarm'],
      });

      return { measurements: response, sensor: searchSensor, word: searchWord };
    }

    if (Number(sensor_id) === -1 && Number(word) === -1) {
      const sensors = await Sensor.findAll({
        include: [
          {
            model: Word,
            as: 'words',
            attributes: ['word', 'name', 'alarm'],
            where: { alarm: true },
          },
        ],
      });

      await Promise.all(
        sensors.map(async (sensor) => {
          await Promise.all(
            sensor.words.map(async (sensorWord) => {
              measurements.push(
                await getMeasurements(sensor.sensor_id, sensorWord.word)
              );
            })
          );
        })
      );
    } else if (Number(sensor_id) !== -1 && Number(word) === -1) {
      const sensors = await Sensor.findOne({
        where: { sensor_id },
        include: [
          {
            model: Word,
            as: 'words',
            attributes: ['word', 'name', 'alarm'],
            where: { alarm: true },
          },
        ],
      });

      await Promise.all(
        sensors.words.map(async (sensorWord) => {
          measurements.push(
            await getMeasurements(sensors.sensor_id, sensorWord.word)
          );
        })
      );
    } else {
      measurements = await getMeasurements(sensor_id, word);
    }

    return res.json(measurements);
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
