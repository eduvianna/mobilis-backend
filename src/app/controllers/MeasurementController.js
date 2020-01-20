import * as Yup from 'yup';

import Measurement from '../models/Measurement';

class MeasurementController {
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
