import * as Yup from 'yup';

import Word from '../models/Word';

class WordController {
  async index(req, res) {
    const { sensor_id, alarm = false } = req.query;

    const words = await Word.findAll({ where: { sensor_id, alarm } });

    return res.json(words);
  }

  async store(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      word: Yup.number().required(),
      name: Yup.string().required(),
      alarm: Yup.boolean().required(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações Invalidas' });
    }

    const wordExists = await Word.findOne({
      where: { sensor_id: req.body.sensor_id, word: req.body.word },
    });

    if (wordExists) {
      return res
        .status(401)
        .json({ error: 'Palavra já registrada para este sensor' });
    }

    const { sensor_id, word, name, alarm } = await Word.create(req.body);

    return res.json({ sensor_id, word, name, alarm });
  }

  async update(req, res) {
    const schema = Yup.object().shape({
      sensor_id: Yup.string().required(),
      oldWord: Yup.number(),
      word: Yup.number().when('oldWord', (oldWord, field) =>
        oldWord ? field.required() : field
      ),
      name: Yup.string(),
      alarm: Yup.boolean(),
    });

    if (!(await schema.isValid(req.body))) {
      return res.status(401).json({ error: 'Informações Invalidas' });
    }
    const checkWord = await Word.findOne({
      where: { sensor_id: req.body.sensor_id, word: req.body.oldWord },
    });

    if (!checkWord) {
      return res.status(401).json({
        error: 'Não existe nenhum sensor com está palavra cadastrada',
      });
    }

    if (req.body.word === checkWord.word) {
      return res.status(401).json({ error: 'Esta palavra já esta em uso' });
    }

    await checkWord.update(req.body);

    const { sensor_id, word, name, alarm } = await Word.findOne({
      where: { sensor_id: req.body.sensor_id, word: req.body.word },
    });

    return res.json({ sensor_id, word, name, alarm });
  }
}

export default new WordController();
