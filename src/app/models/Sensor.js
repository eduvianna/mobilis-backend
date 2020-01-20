import Sequelize, { Model } from 'sequelize';

class Sensor extends Model {
  static init(sequelize) {
    super.init(
      {
        name: Sequelize.STRING,
        description: Sequelize.STRING,
        type: Sequelize.STRING,
        word: Sequelize.INTEGER,
      },
      {
        sequelize,
        tableName: 'sensors',
      }
    );

    return this;
  }
}

export default Sensor;
