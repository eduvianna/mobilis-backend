import Sequelize, { Model } from 'sequelize';

class Word extends Model {
  static init(sequelize) {
    super.init(
      {
        sensor_id: Sequelize.STRING,
        word: Sequelize.INTEGER,
        name: Sequelize.STRING,
        alarm: Sequelize.BOOLEAN,
      },
      {
        sequelize,
        tableName: 'word',
      }
    );

    return this;
  }
}

export default Word;
